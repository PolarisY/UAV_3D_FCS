/*
 * socket.h
 *
 *  Created on: 2012-3-2
 *      Author: youngwolf
 *		email: mail2tao@163.com
 *		QQ: 676218192
 *		Community on QQ: 198941541
 *
 * UDP socket
 */

#ifndef _ASCS_UDP_SOCKET_H_
#define _ASCS_UDP_SOCKET_H_

#include "../socket.h"

namespace ascs { namespace udp {

template <typename Packer, typename Unpacker, typename Socket = asio::ip::udp::socket>
class socket_base : public socket<Socket, Packer, Unpacker, udp_msg<typename Packer::msg_type>, udp_msg<typename Unpacker::msg_type>>
{
protected:
	typedef socket<Socket, Packer, Unpacker, udp_msg<typename Packer::msg_type>, udp_msg<typename Unpacker::msg_type>> super;

public:
	typedef udp_msg<typename Packer::msg_type> in_msg_type;
	typedef const in_msg_type in_msg_ctype;
	typedef udp_msg<typename Unpacker::msg_type> out_msg_type;
	typedef const out_msg_type out_msg_ctype;

public:
	using super::TIMER_BEGIN;
	using super::TIMER_END;

	socket_base(asio::io_service& io_service_) : super(io_service_), unpacker_(std::make_shared<Unpacker>()) {}

	//reset all, be ensure that there's no any operations performed on this udp::socket when invoke it
	//please note, when reuse this udp::socket, object_pool will invoke reset(), child must re-write this to initialize
	//all member variables, and then do not forget to invoke udp::socket::reset() to initialize father's
	//member variables
	virtual void reset()
	{
		reset_state();
		super::reset();

		asio::error_code ec;
		ASCS_THIS lowest_layer().open(local_addr.protocol(), ec); assert(!ec);
#ifndef ASCS_NOT_REUSE_ADDRESS
		ASCS_THIS lowest_layer().set_option(asio::socket_base::reuse_address(true), ec); assert(!ec);
#endif
		ASCS_THIS lowest_layer().bind(local_addr, ec); assert(!ec);
		if (ec)
			unified_out::error_out("bind failed.");
	}

	void reset_state()
	{
		unpacker_->reset_state();
		super::reset_state();
	}

	bool set_local_addr(unsigned short port, const std::string& ip = std::string())
	{
		if (ip.empty())
			local_addr = asio::ip::udp::endpoint(ASCS_UDP_DEFAULT_IP_VERSION, port);
		else
		{
			asio::error_code ec;
			auto addr = asio::ip::address::from_string(ip, ec);
			if (ec)
				return false;

			local_addr = asio::ip::udp::endpoint(addr, port);
		}

		return true;
	}
	const asio::ip::udp::endpoint& get_local_addr() const {return local_addr;}

	void disconnect() {force_close();}
	void force_close() {show_info("link:", "been closed."); do_close();}
	void graceful_close() {force_close();}

	//get or change the unpacker at runtime
	//changing unpacker at runtime is not thread-safe, this operation can only be done in on_msg(), reset() or constructor, please pay special attention
	//we can resolve this defect via mutex, but i think it's not worth, because this feature is not frequently used
	std::shared_ptr<i_unpacker<typename Packer::msg_type>> inner_unpacker() {return unpacker_;}
	std::shared_ptr<const i_unpacker<typename Packer::msg_type>> inner_unpacker() const {return unpacker_;}
	void inner_unpacker(const std::shared_ptr<i_unpacker<typename Packer::msg_type>>& _unpacker_) {unpacker_ = _unpacker_;}

	using super::send_msg;
	///////////////////////////////////////////////////
	//msg sending interface
	UDP_SEND_MSG(send_msg, false) //use the packer with native = false to pack the msgs
	UDP_SEND_MSG(send_native_msg, true) //use the packer with native = true to pack the msgs
	//guarantee send msg successfully even if can_overflow equal to false
	//success at here just means put the msg into udp::socket's send buffer
	UDP_SAFE_SEND_MSG(safe_send_msg, send_msg)
	UDP_SAFE_SEND_MSG(safe_send_native_msg, send_native_msg)
	//like safe_send_msg and safe_send_native_msg, but non-block
	UDP_POST_MSG(post_msg, false)
	UDP_POST_MSG(post_native_msg, true)
	//msg sending interface
	///////////////////////////////////////////////////

	void show_info(const char* head, const char* tail) const {unified_out::info_out("%s %s:%hu %s", head, local_addr.address().to_string().c_str(), local_addr.port(), tail);}

protected:
	virtual bool do_start()
	{
		if (!ASCS_THIS stopped())
		{
			do_recv_msg();
			return true;
		}

		return false;
	}

	//must mutex send_msg_buffer before invoke this function
	virtual bool do_send_msg()
	{
		if (!is_send_allowed() || ASCS_THIS stopped())
			ASCS_THIS sending = false;
		else if (!ASCS_THIS sending && !ASCS_THIS send_msg_buffer.empty())
		{
			ASCS_THIS sending = true;
			ASCS_THIS stat.send_delay_sum += super::statistic::now() - ASCS_THIS send_msg_buffer.front().begin_time;
			ASCS_THIS send_msg_buffer.front().swap(last_send_msg);
			ASCS_THIS send_msg_buffer.pop_front();

			std::shared_lock<std::shared_mutex> lock(close_mutex);
			last_send_msg.restart();
			ASCS_THIS next_layer().async_send_to(asio::buffer(last_send_msg.data(), last_send_msg.size()), last_send_msg.peer_addr,
				ASCS_THIS make_handler_error_size(std::bind(&socket_base::send_handler, this, std::placeholders::_1, std::placeholders::_2)));
		}

		return ASCS_THIS sending;
	}

	virtual void do_recv_msg()
	{
		auto recv_buff = unpacker_->prepare_next_recv();
		assert(asio::buffer_size(recv_buff) > 0);

		std::shared_lock<std::shared_mutex> lock(close_mutex);
		ASCS_THIS next_layer().async_receive_from(recv_buff, peer_addr,
			ASCS_THIS make_handler_error_size(std::bind(&socket_base::recv_handler, this, std::placeholders::_1, std::placeholders::_2)));
	}

	virtual bool is_send_allowed() const {return ASCS_THIS lowest_layer().is_open() && super::is_send_allowed();}
	//can send data or not(just put into send buffer)

	virtual void on_recv_error(const asio::error_code& ec)
	{
		if (asio::error::operation_aborted != ec)
			unified_out::error_out("recv msg error (%d %s)", ec.value(), ec.message().data());
	}

#ifndef ASCS_FORCE_TO_USE_MSG_RECV_BUFFER
	virtual bool on_msg(out_msg_type& msg) {unified_out::debug_out("recv(" ASCS_SF "): %s", msg.size(), msg.data()); return true;}
#endif

	virtual bool on_msg_handle(out_msg_type& msg, bool link_down) {unified_out::debug_out("recv(" ASCS_SF "): %s", msg.size(), msg.data()); return true;}

	void do_close()
	{
		ASCS_THIS stop_all_timer();
		ASCS_THIS started_ = false;
//		ASCS_THIS reset_state();

		if (ASCS_THIS lowest_layer().is_open())
		{
			asio::error_code ec;
			ASCS_THIS lowest_layer().shutdown(asio::ip::udp::socket::shutdown_both, ec);

			std::unique_lock<std::shared_mutex> lock(close_mutex);
			ASCS_THIS lowest_layer().close(ec);
		}
	}

private:
	void recv_handler(const asio::error_code& ec, size_t bytes_transferred)
	{
		if (!ec && bytes_transferred > 0)
		{
			++ASCS_THIS stat.recv_msg_sum;
			ASCS_THIS stat.recv_byte_sum += bytes_transferred;
			ASCS_THIS temp_msg_buffer.resize(ASCS_THIS temp_msg_buffer.size() + 1);
			ASCS_THIS temp_msg_buffer.back().swap(peer_addr, unpacker_->parse_msg(bytes_transferred));
			ASCS_THIS dispatch_msg();
		}
#ifdef _MSC_VER
		else if (asio::error::connection_refused == ec || asio::error::connection_reset == ec)
			do_start();
#endif
		else
			on_recv_error(ec);
	}

	void send_handler(const asio::error_code& ec, size_t bytes_transferred)
	{
		if (!ec)
		{
			assert(bytes_transferred == last_send_msg.size());

			ASCS_THIS stat.send_time_sum += super::statistic::now() - last_send_msg.begin_time;
			ASCS_THIS stat.send_byte_sum += bytes_transferred;
			++ASCS_THIS stat.send_msg_sum;
#ifdef ASCS_WANT_MSG_SEND_NOTIFY
			ASCS_THIS on_msg_send(last_send_msg);
#endif
		}
		else
			ASCS_THIS on_send_error(ec);

#ifdef ASCS_WANT_ALL_MSG_SEND_NOTIFY
		typename super::in_msg msg;
		msg.swap(last_send_msg);
#endif
		last_send_msg.clear();

		std::unique_lock<std::shared_mutex> lock(ASCS_THIS send_msg_buffer_mutex);
		ASCS_THIS sending = false;

		//send msg sequentially, that means second send only after first send success
		//under windows, send a msg to addr_any may cause sending errors, please note
		//for UDP in ascs, sending error will not stop the following sending.
#ifdef ASCS_WANT_ALL_MSG_SEND_NOTIFY
		if (!do_send_msg())
			ASCS_THIS on_all_msg_send(msg);
#else
		do_send_msg();
#endif
	}

protected:
	typename super::in_msg last_send_msg;
	std::shared_ptr<i_unpacker<typename Packer::msg_type>> unpacker_;
	asio::ip::udp::endpoint peer_addr, local_addr;

	std::shared_mutex close_mutex;
};

}} //namespace

#endif /* _ASCS_UDP_SOCKET_H_ */
