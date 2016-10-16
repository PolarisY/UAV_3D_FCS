/*
 * service_pump.h
 *
 *  Created on: 2012-3-2
 *      Author: youngwolf
 *		email: mail2tao@163.com
 *		QQ: 676218192
 *		Community on QQ: 198941541
 *
 * this class only used at both server and client endpoint
 */

#ifndef _ASCS_SERVICE_PUMP_H_
#define _ASCS_SERVICE_PUMP_H_

#include "base.h"

namespace ascs
{

class service_pump : public asio::io_service
{
public:
	class i_service
	{
	protected:
		i_service(service_pump& service_pump_) : sp(service_pump_), started(false), id_(0), data(nullptr) {service_pump_.add(this);}
		virtual ~i_service() {}

	public:
		//for the same i_service, start_service and stop_service are not thread safe,
		//to resolve this defect, we must add a mutex member variable to i_service, it's not worth
		void start_service() {if (!started) started = init();}
		void stop_service() {if (started) uninit(); started = false;}
		bool is_started() const {return started;}

		void id(int id) {id_ = id;}
		int id() const {return id_;}
		void user_data(void* data_) {data = data_;}
		void* user_data() const {return data;}

		service_pump& get_service_pump() {return sp;}
		const service_pump& get_service_pump() const {return sp;}

	protected:
		virtual bool init() = 0;
		virtual void uninit() = 0;

	protected:
		service_pump& sp;

	private:
		bool started;
		int id_;
		void* data; //magic data, you can use it in any way
	};

public:
	typedef i_service* object_type;
	typedef const object_type object_ctype;
	typedef std::list<object_type> container_type;

	service_pump() : started(false) {}

	object_type find(int id)
	{
		std::shared_lock<std::shared_mutex> lock(service_can_mutex);
		auto iter = std::find_if(std::begin(service_can), std::end(service_can), [id](object_ctype& item) {return id == item->id();});
		return iter == std::end(service_can) ? nullptr : *iter;
	}

	void remove(object_type i_service_)
	{
		assert(nullptr != i_service_);

		std::unique_lock<std::shared_mutex> lock(service_can_mutex);
		service_can.remove(i_service_);
		lock.unlock();

		stop_and_free(i_service_);
	}

	void remove(int id)
	{
		std::unique_lock<std::shared_mutex> lock(service_can_mutex);
		auto iter = std::find_if(std::begin(service_can), std::end(service_can), [id](object_ctype& item) {return id == item->id();});
		if (iter != std::end(service_can))
		{
			auto i_service_ = *iter;
			service_can.erase(iter);
			lock.unlock();

			stop_and_free(i_service_);
		}
	}

	void clear()
	{
		container_type temp_service_can;

		std::unique_lock<std::shared_mutex> lock(service_can_mutex);
		temp_service_can.splice(std::end(temp_service_can), service_can);
		lock.unlock();

		ascs::do_something_to_all(temp_service_can, [this](object_type& item) {ASCS_THIS stop_and_free(item);});
	}

	void start_service(int thread_num = ASCS_SERVICE_THREAD_NUM) {if (!is_service_started()) do_service(thread_num);}
	//stop the service, must be invoked explicitly when the service need to stop, for example, close the application
	void stop_service()
	{
		if (is_service_started())
		{
			end_service();
			wait_service();
		}
	}

	//if you add a service after start_service, use this to start it
	void start_service(object_type i_service_, int thread_num = ASCS_SERVICE_THREAD_NUM)
	{
		assert(nullptr != i_service_);

		if (is_service_started())
			i_service_->start_service();
		else
			start_service(thread_num);
	}
	void stop_service(object_type i_service_) {assert(nullptr != i_service_); i_service_->stop_service();}

	//this function works like start_service except that it will block until all services run out
	void run_service(int thread_num = ASCS_SERVICE_THREAD_NUM)
	{
		if (!is_service_started())
		{
			do_service(thread_num - 1);

			asio::error_code ec;
			run(ec);

			wait_service();
		}
	}
	//stop the service, must be invoked explicitly when the service need to stop, for example, close the application
	//only for service pump started by 'run_service', this function will return immediately,
	//only the return from 'run_service' means service pump ended.
	void end_service() {if (is_service_started()) do_something_to_all([](object_type& item) {item->stop_service();});}

	bool is_running() const {return !stopped();}
	bool is_service_started() const {return started;}
	void add_service_thread(int thread_num) {for (auto i = 0; i < thread_num; ++i) service_threads.push_back(std::thread([this]() {asio::error_code ec; ASCS_THIS run(ec);}));}

protected:
	void do_service(int thread_num)
	{
		started = true;
		unified_out::info_out("service pump started.");

		reset(); //this is needed when restart service
		do_something_to_all([](object_type& item) {item->start_service();});
		add_service_thread(thread_num);
	}
	void wait_service() {ascs::do_something_to_all(service_threads, [](std::thread& t) {t.join();}); unified_out::info_out("service pump end."); started = false;}

	void stop_and_free(object_type i_service_)
	{
		assert(nullptr != i_service_);

		i_service_->stop_service();
		free(i_service_);
	}
	virtual void free(object_type i_service_) {} //if needed, rewrite this to free the service

#ifdef ASCS_ENHANCED_STABILITY
	virtual bool on_exception(const std::exception& e)
	{
		unified_out::error_out("service pump exception: %s.", e.what());
		return true; //continue this io_service::run, if needed, rewrite this to decide whether to continue or not
	}

	size_t run(asio::error_code& ec)
	{
		while (true)
		{
			try {return io_service::run(ec);}
			catch (const std::exception& e) {if (!on_exception(e)) return 0;}
		}
	}
#endif

	DO_SOMETHING_TO_ALL_MUTEX(service_can, service_can_mutex)
	DO_SOMETHING_TO_ONE_MUTEX(service_can, service_can_mutex)

private:
	void add(object_type i_service_)
	{
		assert(nullptr != i_service_);

		std::unique_lock<std::shared_mutex> lock(service_can_mutex);
		service_can.push_back(i_service_);
	}

protected:
	container_type service_can;
	std::shared_mutex service_can_mutex;
	std::list<std::thread> service_threads;
	bool started;
};

} //namespace

#endif /* _ASCS_SERVICE_PUMP_H_ */
