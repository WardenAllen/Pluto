
/*
 * @author WardenAllen
 * @date   2021/01/04 14:32:04
 * @brief  
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "time_util.h"
#include "type_traits_util.h"
#include "singleton.h"

class time_monitor_t : 
	public pluto::util::singleton_t<time_monitor_t>
{
	struct point_t {

		explicit point_t(int64_t t, void* d = nullptr) :
			cost(t), data(d) { }

		int64_t cost;
		void* data;
	};

	using point_ary_t = std::vector<point_t>;

	struct monitor_t {
		point_ary_t points;
		pluto::util::clock_t<std::chrono::nanoseconds> clock;
	};

public:
	time_monitor_t();
	~time_monitor_t();

public:
	/* for time usage, name must be valid! */
	bool reg_monitor(std::string name);
	void clear(std::string name);
	void start(std::string name);
	void lap(std::string name);

	/* push a special point into points. */
	void pause(std::string name);

	template <class Unit = std::chrono::milliseconds>
	void print(std::string name) {

		auto& monitor = _monitors[name];

		std::cout << name << "'s Time Cost" << std::endl;

		using traits = pluto::util::chrono_trait_t<Unit>;

		int64_t last = 0;

		for (int i = 0; i < (int)monitor.points.size(); i++) {

			auto cost = monitor.points[i].cost;

			std::cout << "lap " << i+1 << " cost " <<
				static_cast<int64_t>((cost - last)/ traits::den) <<
				" " << traits::unit_name << std::endl;

			last = cost;
		}

		std::cout << "total cost " <<
			static_cast<int64_t>(monitor.points.back().cost / traits::den) << 
			" " << traits::unit_name << std::endl;
	}

private:
	std::unordered_map<std::string, monitor_t> _monitors;

};

