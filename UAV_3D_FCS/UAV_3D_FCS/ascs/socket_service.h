/*
 * socket_service.h
 *
 *  Created on: 2012-3-2
 *      Author: youngwolf
 *		email: mail2tao@163.com
 *		QQ: 676218192
 *		Community on QQ: 198941541
 *
 * this class only used at client endpoint
 */

#ifndef _ASCS_SOCKET_SERVICE_H_
#define _ASCS_SOCKET_SERVICE_H_

#include "object_pool.h"

namespace ascs
{

//only support one socket
template<typename Socket>
class single_socket_service : public service_pump::i_service, public Socket
{
public:
	using Socket::TIMER_BEGIN;
	using Socket::TIMER_END;

	single_socket_service(service_pump& service_pump_) : i_service(service_pump_), Socket(service_pump_) {}
	template<typename Arg>
	single_socket_service(service_pump& service_pump_, Arg& arg) : i_service(service_pump_), Socket(service_pump_, arg) {}

protected:
	virtual bool init() {ASCS_THIS reset(); ASCS_THIS start(); return Socket::started();}
	virtual void uninit() {ASCS_THIS graceful_close();}
};

template<typename Socket, typename Pool>
class multi_socket_service : public Pool
{
protected:
	using Pool::TIMER_BEGIN;
	using Pool::TIMER_END;

	multi_socket_service(service_pump& service_pump_) : Pool(service_pump_) {}
	template<typename Arg>
	multi_socket_service(service_pump& service_pump_, Arg arg) : Pool(service_pump_, arg) {}

	virtual bool init()
	{
		ASCS_THIS do_something_to_all([](typename Pool::object_ctype& item) {item->reset(); item->start();});
		ASCS_THIS start();
		return true;
	}

public:
	//parameter reset valid only if the service pump already started, or service pump will call object pool's init function before start service pump
	bool add_socket(typename Pool::object_ctype& socket_ptr, bool reset = true)
	{
		if (ASCS_THIS add_object(socket_ptr))
		{
			if (ASCS_THIS get_service_pump().is_service_started()) //service already started
			{
				if (reset)
					socket_ptr->reset();
				socket_ptr->start();
			}

			return true;
		}

		return false;
	}

	//unseal object creation.
	using Pool::create_object;
};

} //namespace

#endif /* _ASCS_SOCKET_SERVICE_H_ */
