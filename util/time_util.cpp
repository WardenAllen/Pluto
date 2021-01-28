
/*
 * @author WardenAllen
 * @date   2020/08/31 19:58:14
 * @brief  
 */

#include <sstream>
#include <iomanip>

#include "time_util.h"

namespace pluto
{
namespace util
{

std::string today_string(char delim)
{
	std::string time;
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);

	std::stringstream ss;
	ss << local_tm.tm_year + 1900 << delim;
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1 << delim;
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mday;

	ss >> time;
	return time;
}

std::string time_stamp_string(int64_t ts)
{
	time_t t = (time_t)ts;
	tm local_tm = *localtime(&t);

	std::string date;
	std::string time;

	std::stringstream ss;
	ss << local_tm.tm_year + 1900 << "-";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1 << "-";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mday;
	ss >> date;

	ss.clear();
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_hour << ":";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_min << ":";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

	ss >> time;

	return date + " " + time;
}

std::string now_string()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);

	std::string date;
	std::string time;

	std::stringstream ss;
	ss << local_tm.tm_year + 1900 << "-";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mon + 1 << "-";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_mday;
	ss >> date;

	ss.clear();
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_hour << ":";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_min << ":";
	ss << std::setfill('0') << std::setw(2) << local_tm.tm_sec;

	ss >> time;

	return date + " " + time;
}

int get_year()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_year;
}

int get_month()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mon;
}

int get_day()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_mday;
}

int get_week_day()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_wday;
}

int get_year_day()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_yday;
}

int get_hour()
{
	time_t tt = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	tm local_tm = *localtime(&tt);
	return local_tm.tm_hour;
}

} // util
} // pluto