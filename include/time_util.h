#pragma once

/*
 * @author WardenAllen
 * @date   2020/08/31 19:58:14
 * @brief
 */

#include <chrono>
#include <string>
#include <inttypes.h>

#include "define.h"

namespace pluto
{
namespace util
{

std::string today_string(char delim = 0);
std::string time_stamp_string(int64_t ts);
std::string now_string();

int get_year();
int get_month();
int get_day();
int get_week_day();
int get_year_day();
int get_hour();

template <class T = std::chrono::seconds, class Ret = int64_t>
Ret now() 
{
	static_assert(std::is_integral<Ret>::value,
		"RET must be int, uint32_t, int64_t or uint64_t!");

	return static_cast<Ret>(std::chrono::duration_cast<T>(
		std::chrono::system_clock::now().time_since_epoch())
		.count());
}

template <class Ret = int64_t>
Ret nowns() {
	return now<std::chrono::nanoseconds, Ret>();
}

template <class Ret = int64_t>
Ret nowus() {
	return now<std::chrono::microseconds, Ret>();
}

template <class Ret = int64_t>
Ret nowms() {
	return now<std::chrono::milliseconds, Ret>();
}

template <class T = std::chrono::seconds, class Ret = int64_t>
class clock_t
{
	static_assert(std::is_integral<Ret>::value, 
		"RET must be int, uint32_t, int64_t or uint64_t!");

public:
	clock_t() { reset(); }
	~clock_t() = default;

public:
	void reset() { 
		_point = std::chrono::system_clock::time_point(); 
	}

	Ret start() {
		_point = std::chrono::system_clock::now();
		return static_cast<Ret>(std::chrono::duration_cast<T>(
			_point.time_since_epoch()).count());
	}

	Ret lap() {
		return static_cast<Ret>(std::chrono::duration_cast<T>(
			(std::chrono::system_clock::now() - _point)).count());
	}

	Ret stop() {
		auto start = _point;
		_point = std::chrono::system_clock::now();
		return static_cast<Ret>(std::chrono::duration_cast<T>(
			(_point - start)).count());
	}

private:
	std::chrono::system_clock::time_point _point;
};


} // util
} // pluto
