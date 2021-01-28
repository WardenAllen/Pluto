
/*
 * @author WardenAllen
 * @date   2020/09/11 14:56:37
 * @brief  
 */

#include <functional>
#include <gtest/gtest.h>

#include "timer.h"

using namespace std;
using namespace pluto::base;

TEST(PLUTO, STATIC_TIMER) {
	
	{
		single_timer_t timer;
		timer.add(1, -1);
		timer.set_cb([](void) {
			std::cout << "single run" << std::endl;
		});
		timer.run();
	}

	{
		multi_timer_t<> timer;

		timer.set_cb(1, [](void) {
			std::cout << "static run" << std::endl;
			});

		for (int i = 0; i < 10; i++)
		{
			timer.add(i, 1, -1, nullptr);
		}

		for (int i = 0; i < 10; i++)
		{
			timer.run();
		}
	}


}

TEST(PLUTO, DYNAMIC_TIMER) {

	using Callback = std::function<void(void*)>;

	struct timer_data_t : public 
		dynamic_data_base_t<Callback> 
	{
		timer_data_t(Callback cb_, int loop_, void* data_) {

			// TODO: WHY CANNOT USE INITIALIZER LIST HERE???

			loop = loop_;
			cb = cb_;
			data = data_;
		}
	};

	dynamic_timer_t timer;
	// same as : dynamic_timer_t<dynamic_data_base_t<Callback>> timer;

	Callback cb = [](void*) {
		std::cout << "dynamic run" << std::endl;
	};
	
	for (int i = 0; i < 10; i++)
	{
		timer.add(i, cb, -1, nullptr);
	}

	for (int i = 0; i < 10; i++)
	{
		timer.run();
	}

}
