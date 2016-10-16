/*
 * object_pool.h
 *
 *  Created on: 2013-8-7
 *      Author: youngwolf
 *		email: mail2tao@163.com
 *		QQ: 676218192
 *		Community on QQ: 198941541
 *
 * this class used at both client and server endpoint, and in both TCP and UDP socket
 * this class can only manage objects that inherit from socket
 */

#ifndef _ASCS_OBJECT_POOL_H_
#define _ASCS_OBJECT_POOL_H_

#include <atomic>
#include <unordered_map>

#include "timer.h"
#include "service_pump.h"

namespace ascs
{

template<typename Object>
class object_pool : public service_pump::i_service, public timer
{
public:
	typedef std::shared_ptr<Object> object_type;
	typedef const object_type object_ctype;
	typedef std::unordered_map<uint_fast64_t, object_type> container_type;

protected:
	struct invalid_object
	{
		object_ctype object_ptr;

#ifdef ASCS_ENHANCED_STABILITY
		invalid_object(object_ctype& object_ptr_) : object_ptr(object_ptr_) {assert(object_ptr);}

		bool is_timeout() const {return true;}
		bool is_timeout(time_t now) const {return true;}
#else
		const time_t kick_out_time;
		invalid_object(object_ctype& object_ptr_) : object_ptr(object_ptr_), kick_out_time(time(nullptr)) {assert(object_ptr);}

		bool is_timeout() const {return is_timeout(time(nullptr));}
		bool is_timeout(time_t now) const {return kick_out_time <= now - ASCS_OBSOLETED_OBJECT_LIFE_TIME;}
#endif
	};

protected:
	static const unsigned char TIMER_BEGIN = timer::TIMER_END;
	static const unsigned char TIMER_FREE_SOCKET = TIMER_BEGIN;
	static const unsigned char TIMER_CLEAR_SOCKET = TIMER_BEGIN + 1;
	static const unsigned char TIMER_END = TIMER_BEGIN + 10;

	object_pool(service_pump& service_pump_) : i_service(service_pump_), timer(service_pump_), cur_id(-1), max_size_(ASCS_MAX_OBJECT_NUM) {}

	void start()
	{
#ifdef ASCS_FREE_OBJECT_INTERVAL
		set_timer(TIMER_FREE_SOCKET, 1000 * ASCS_FREE_OBJECT_INTERVAL, [this](unsigned char id)->bool {ASCS_THIS free_object(); return true;});
#endif
#ifdef ASCS_CLEAR_OBJECT_INTERVAL
		set_timer(TIMER_CLEAR_SOCKET, 1000 * ASCS_CLEAR_OBJECT_INTERVAL, [this](unsigned char id)->bool {ASCS_THIS clear_obsoleted_object(); return true;});
#endif
	}

	void stop() {stop_all_timer();}

	bool add_object(object_ctype& object_ptr)
	{
		assert(object_ptr);

		std::unique_lock<std::shared_mutex> lock(object_can_mutex);
		return object_can.size() < max_size_ ? object_can.insert(std::make_pair(object_ptr->id(), object_ptr)).second : false;
	}

	//only add object_ptr to invalid_object_can when it's in object_can, this can avoid duplicated items in invalid_object_can, because invalid_object_can is a list,
	//there's no way to check the existence of an item in a list efficiently.
	bool del_object(object_ctype& object_ptr)
	{
		assert(object_ptr);

		std::unique_lock<std::shared_mutex> lock(object_can_mutex);
		auto exist = object_can.erase(object_ptr->id()) > 0;
		lock.unlock();

		if (exist)
		{
			std::unique_lock<std::shared_mutex> lock(invalid_object_can_mutex);
			invalid_object_can.push_back(object_ptr);
		}

		return exist;
	}

	virtual void on_create(object_ctype& object_ptr) {}

	void init_object(object_ctype& object_ptr)
	{
		if (object_ptr)
		{
			object_ptr->id(++cur_id);
			on_create(object_ptr);
		}
		else
			unified_out::error_out("create object failed!");
	}

#ifdef ASCS_REUSE_OBJECT
	object_type reuse_object()
	{
		std::unique_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		//objects are order by time, so we don't have to go through all items in invalid_object_can
		for (auto iter = std::begin(invalid_object_can); iter != std::end(invalid_object_can) && iter->is_timeout(); ++iter)
			if (iter->object_ptr.unique() && iter->object_ptr->obsoleted())
			{
				auto object_ptr(std::move(iter->object_ptr));
				invalid_object_can.erase(iter);
				lock.unlock();

				object_ptr->reset();
				return object_ptr;
			}

		return object_type();
	}

	template<typename Arg>
	object_type create_object(Arg& arg)
	{
		auto object_ptr = reuse_object();
		if (!object_ptr)
			object_ptr = std::make_shared<Object>(arg);

		init_object(object_ptr);
		return object_ptr;
	}

	template<typename Arg1, typename Arg2>
	object_type create_object(Arg1& arg1, Arg2& arg2)
	{
		auto object_ptr = reuse_object();
		if (!object_ptr)
			object_ptr = std::make_shared<Object>(arg1, arg2);

		init_object(object_ptr);
		return object_ptr;
	}
#else
	template<typename Arg>
	object_type create_object(Arg& arg)
	{
		auto object_ptr = std::make_shared<Object>(arg);
		init_object(object_ptr);
		return object_ptr;
	}

	template<typename Arg1, typename Arg2>
	object_type create_object(Arg1& arg1, Arg2& arg2)
	{
		auto object_ptr = std::make_shared<Object>(arg1, arg2);
		init_object(object_ptr);
		return object_ptr;
	}
#endif

	object_type create_object() {return create_object(sp);}

public:
	//to configure unordered_set(for example, set factor or reserved size), not locked the mutex, so must be called before service_pump starting up.
	container_type& container() {return object_can;}

	size_t max_size() const {return max_size_;}
	void max_size(size_t _max_size) {max_size_ = _max_size;}

	size_t size()
	{
		std::shared_lock<std::shared_mutex> lock(object_can_mutex);
		return object_can.size();
	}

	size_t invalid_object_size()
	{
		std::shared_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		return invalid_object_can.size();
	}

	object_type find(uint_fast64_t id)
	{
		std::shared_lock<std::shared_mutex> lock(object_can_mutex);
		auto iter = object_can.find(id);
		return iter != std::end(object_can) ? iter->second : object_type();
	}

	//this method has linear complexity, please note.
	object_type at(size_t index)
	{
		std::shared_lock<std::shared_mutex> lock(object_can_mutex);
		assert(index < object_can.size());
		return index < object_can.size() ? std::next(std::begin(object_can), index)->second : object_type();
	}

	//this method has linear complexity, please note.
	object_type invalid_object_at(size_t index)
	{
		std::shared_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		assert(index < invalid_object_can.size());
		return index < invalid_object_can.size() ? std::next(std::begin(invalid_object_can), index)->object_ptr : object_type();
	}

	//this method has linear complexity, please note.
	object_type invalid_object_find(uint_fast64_t id)
	{
		std::shared_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		auto iter = std::find_if(std::begin(invalid_object_can), std::end(invalid_object_can), [id](const invalid_object& item) {return id == item.object_ptr->id();});
		return iter == std::end(invalid_object_can) ? object_type() : iter->object_ptr;
	}

	//this method has linear complexity, please note.
	object_type invalid_object_pop(uint_fast64_t id)
	{
		std::shared_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		auto iter = std::find_if(std::begin(invalid_object_can), std::end(invalid_object_can), [id](const invalid_object& item) {return id == item.object_ptr->id();});
		if (iter != std::end(invalid_object_can))
		{
			auto object_ptr = iter->object_ptr;
			invalid_object_can.erase(iter);
			return object_ptr;
		}
		return object_type();
	}

	void list_all_object() {do_something_to_all([](object_ctype& item) {item->show_info("", ""); });}

	//Kick out obsoleted objects
	//Consider the following assumptions:
	//1.You didn't invoke del_object in on_recv_error or other places.
	//2.For some reason(I haven't met yet), on_recv_error not been invoked
	//object_pool will automatically invoke this function if ASCS_CLEAR_OBJECT_INTERVAL been defined
	size_t clear_obsoleted_object()
	{
		std::list<object_type> objects;

		std::unique_lock<std::shared_mutex> lock(object_can_mutex);
		for (auto iter = std::begin(object_can); iter != std::end(object_can);)
			if (iter->second.unique() && iter->second->obsoleted())
			{
#ifdef ASCS_REUSE_OBJECT
				iter->second->show_info("object:", "is obsoleted, kick it out, it will be reused in the future.");
#else
				iter->second->show_info("object:", "is obsoleted, kick it out, it will be freed in the future.");
#endif
#ifdef ASCS_ENHANCED_STABILITY
				iter->second->close();
#endif
				objects.push_back(iter->second);
				iter = object_can.erase(iter);
			}
			else
				++iter;
		lock.unlock();

		auto size = objects.size();
		if (0 != size)
		{
			unified_out::warning_out(ASCS_SF " object(s) been kicked out!", size);

			std::unique_lock<std::shared_mutex> lock(invalid_object_can_mutex);
			invalid_object_can.insert(std::end(invalid_object_can), std::begin(objects), std::end(objects));
		}

		return size;
	}

	//free or close a specific number of objects
	//if you used object pool(define ASCS_REUSE_OBJECT), you can manually call this function to free some objects after the object pool(invalid_object_size())
	// goes big enough for memory saving(because the objects in invalid_object_can are waiting for reusing and will never be freed),
	// you can also define ASCS_FREE_OBJECT_INTERVAL to let object_pool to call this function automatically and periodically, but objects will only be closed.
	//if you don't used object pool, object_pool will invoke this function automatically and periodically, so you don't need to invoke this function exactly
	//return affected object number, if just_close equal to true, then closed objects will be treated as unaffected.
#ifdef ASCS_REUSE_OBJECT
	size_t free_object(size_t num = -1, bool just_close = true)
#else
	size_t free_object(size_t num = -1, bool just_close = false)
#endif
	{
		size_t num_affected = 0;
		std::unique_lock<std::shared_mutex> lock(invalid_object_can_mutex);
		//objects are order by time, so we don't have to go through all items in invalid_object_can
		for (auto iter = std::begin(invalid_object_can); num > 0 && iter != std::end(invalid_object_can) && iter->is_timeout();)
			if (iter->object_ptr.unique() && iter->object_ptr->obsoleted())
			{
				--num;
				if (just_close)
				{
					if (iter->object_ptr->close())
						++num_affected;
					++iter;
				}
				else
				{
					++num_affected;
					iter = invalid_object_can.erase(iter);
				}
			}
			else
				++iter;

		if (num_affected > 0)
			unified_out::warning_out(ASCS_SF " object(s) been %s!", num_affected, just_close ? "closed" : "freed");

		return num_affected;
	}

	template<typename _Predicate>
	void do_something_to_all(const _Predicate& __pred) {std::shared_lock<std::shared_mutex> lock(object_can_mutex); for (auto& item : object_can) __pred(item.second);}

	template<typename _Predicate> void do_something_to_one(const _Predicate& __pred)
		{std::shared_lock<std::shared_mutex> lock(object_can_mutex); for (auto iter = std::begin(object_can); iter != std::end(object_can); ++iter) if (__pred(iter->second)) break;}

protected:
	std::atomic_uint_fast64_t cur_id;

	container_type object_can;
	std::shared_mutex object_can_mutex;
	size_t max_size_;

	//because all objects are dynamic created and stored in object_can, maybe when receiving error occur
	//(you are recommended to delete the object from object_can, for example via tcp::server_base::del_client), some other asynchronous calls are still queued in asio::io_service,
	//and will be dequeued in the future, we must guarantee these objects not be freed from the heap or reused, so we move these objects from object_can to invalid_object_can,
	//and free them from the heap or reuse them in the near future, see ASCS_OBSOLETED_OBJECT_LIFE_TIME macro for more details.
	//if ASCS_CLEAR_OBJECT_INTERVAL been defined, clear_obsoleted_object() will be invoked automatically and periodically to move all invalid objects into invalid_object_can.
	std::list<invalid_object> invalid_object_can;
	std::shared_mutex invalid_object_can_mutex;
};

} //namespace

#endif /* _ASCS_OBJECT_POOL_H_ */
