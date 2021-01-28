#pragma once

/*
 * @author WardenAllen
 * @date   2020/09/11 14:41:59
 * @brief  
 */

#include <iostream>
#include <map>
#include <array>
#include <functional>

#include <inttypes.h>

#include "stl_util.h"
#include "time_util.h"

namespace pluto
{
namespace base
{

/**
 * TODO: timer_base_t's _timer map data need reused, 
 * use pointer instead of object. use allocator instead
 * of new().
 */

/**
 * timer_base_t is the base class of all timers.
 */

template <class Data = int>
class timer_base_t
{
public:
	virtual ~timer_base_t() { }

public:
	void run() { run(util::now<std::chrono::milliseconds>()); }

public:
	void run(int64_t ts)
	{
		while ((int)_timer.size() > 0)
		{
			auto it = _timer.begin();
			if (ts < it->first) break;
			auto& sd = it->second;

			call(sd);
			after_run<Data>(sd, ts);

			_timer.erase(it);
		}
	}

	template <class Data2 = Data, 
		typename std::enable_if<!std::is_same<Data2, int>::value,
		int>::type = 0>
	void after_run(Data2& sd, int64_t ts)
	{
		if (sd.loop >= 0)
			add(ts + sd.loop, std::move(sd));
	}

	template <class Data2 = Data,
		typename std::enable_if<std::is_same<Data2, 
		int>::value, int>::type = 0>
	void after_run(Data2& sd, int64_t ts)
	{
		if (sd >= 0)
			add(ts + sd, sd);
	}

public:
	template<typename... Args>
	void add(int64_t ts, Args&&... args)
	{
		util::try_emplace(_timer, ts,
			std::forward<Args>(args)...);
	}

	void add(int64_t ts, int loop)
	{
		_timer.emplace(ts, loop);
	}

protected:
	virtual void call(Data&) = 0;

protected:
	std::multimap<int64_t, Data> _timer;
};


/**
 * single_timer_t only has one type callback functions.
 * when use FuncEmpty as the callback, there is no need
 * to set template Data, just use int to save loop.
 */

using default_func_t = std::function<void(void)>;
using default_func_with_data_t = std::function<void(void*)>;

template <class Func = default_func_t, 
	class Data = int>
class single_timer_t :
	public timer_base_t<Data>
{
public:
	virtual ~single_timer_t() = default;

protected:
	virtual void call(Data& sd)
	{
		_cb(sd.data);
	}

public:
	inline void set_cb(Func&& cb) { _cb = cb; }

private:
	Func _cb;
};

/**
 * single_timer_t's partial specialize.
 */

template <>
class single_timer_t <default_func_t, int> :
	public timer_base_t<int>
{
public:
	virtual ~single_timer_t() = default;

protected:
	virtual void call(int&)
	{
		_cb();
	}

public:
	inline void set_cb(default_func_t&& cb) { _cb = cb; }

private:
	default_func_t _cb;
};


/**
 * multi_timer_data_t has at most MAX type callback functions.
 * its default data is multi_timer_data_t because every data
 * needs to save type (or data).
 */


#pragma pack (push, 1)

struct multi_timer_data_t 
{
	multi_timer_data_t() :
		type(-1), loop(-1)
	{ }

	multi_timer_data_t(int t, int l, void* d) :
		type(t), loop(l)
	{ }

	int type;
	int loop;
};

#pragma pack (pop)

template <class Func = default_func_t, 
	int Max = 16, 
	class Data = multi_timer_data_t>
class multi_timer_t :
	public timer_base_t<Data>
{
public:
	virtual ~multi_timer_t() = default;

protected:
	virtual void call(Data& sd)
	{
		_cb_ary[sd.type](sd.data);
	}

public:
	bool set_cb(int type, Func f)
	{
		if (type >= Max) return false;
		_cb_ary[type] = f;
		return true;
	}

private:
	std::array<Func, Max> _cb_ary;
};

/**
 * multi_timer_t's partial specialize.
 */

template <int Max, class Data>
class multi_timer_t<default_func_t, Max, Data> :
	public timer_base_t<Data>
{
public:
	virtual ~multi_timer_t() = default;

protected:
	virtual void call(Data& sd)
	{
		_cb_ary[sd.type]();
	}

public:
	bool set_cb(int type, default_func_t f)
	{
		if (type >= Max) return false;
		_cb_ary[type] = f;
		return true;
	}

private:
	std::array<default_func_t, Max> _cb_ary;
};


/**
 * template derived class cannot see base template 
 * class's protected member and function, so we need 
 * declare 'using' before used, or use this-> / base<>:: 
 * before member and function.
 */


#pragma pack (push, 1)

template <class T>
struct dynamic_data_base_t 
{
	using base_type = T;

	dynamic_data_base_t() :
		cb(), loop(-1), data(nullptr)
	{ }

	dynamic_data_base_t(T& c, int l, void* d) :
		cb(c), loop(l), data(d)
	{ }

	T cb;
	int loop;
	void* data;
};

#pragma pack (pop)

template <class Func = default_func_with_data_t,
	class Data = dynamic_data_base_t<Func>>
class dynamic_timer_t :
	public timer_base_t<Data>
{
	static_assert(std::is_base_of<
		dynamic_data_base_t<typename Data::base_type>, Data>(),
		"T is not derived from dynamic_data_base_t!");

public:
	virtual ~dynamic_timer_t() = default;

protected:
	virtual void call(Data& sd)
	{
		sd.cb(sd.data);
	}

};

} // base
} // pluto
