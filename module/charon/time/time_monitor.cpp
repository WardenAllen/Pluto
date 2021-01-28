
/*
 * @author WardenAllen
 * @date   2021/01/04 11:00:33
 * @brief  
 */

#include "time_monitor.h"

time_monitor_t::time_monitor_t()
{
}

time_monitor_t::~time_monitor_t()
{
}

bool time_monitor_t::reg_monitor(std::string name)
{
	_monitors[name].points.reserve(16);
	return true;
}


void time_monitor_t::clear(std::string name)
{
	_monitors.erase(name);
}

void time_monitor_t::start(std::string name)
{
	auto& monitor = _monitors[name];
	monitor.clock.start();
}

void time_monitor_t::lap(std::string name)
{
	auto& monitor = _monitors[name];
	monitor.points.emplace_back(monitor.clock.lap());
}
