

#ifdef __cplusplus 
#undef __cplusplus 
#define __cplusplus 202002
#endif // __cplusplus 

#include <iostream>
#include <unistd.h>

#include "time_monitor.h"

using namespace std;

int main(int argc, const char* argv[])
{

	time_monitor_t m;

	m.reg_monitor("TEST_MONITOR");
	m.start("TEST_MONITOR");

	usleep(1000);
	m.lap("TEST_MONITOR");

	m.lap("TEST_MONITOR");

	m.lap("TEST_MONITOR");

	m.lap("TEST_MONITOR");

	m.lap("TEST_MONITOR");

	m.print<chrono::nanoseconds>("TEST_MONITOR");

	return 0;
}
