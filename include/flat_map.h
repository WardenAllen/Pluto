#pragma once

/*
 * @author WardenAllen
 * @date   2020/12/03 16:25:05
 * @brief  
 */

#include <map>
#include <memory_resource>

#include "linear_allocator.h"

namespace pluto
{
namespace pmr
{

/*
 * vector's emplace_back() after c++ 14:
 *
 * struct A { string s; };
 * vector<A> vec;
 * auto& a = vec.emplace_back()
 * a.s = "WardenAllen";
 * 
 */

template <class _Key, class _Tp,
	class _Compare = std::less<_Key>>
	class flat_map_t
{
public:
	using _MapType = std::pmr::map<_Key, _Tp, _Compare>;
	using _AllocType = linear_allocator_t<typename _MapType::value_type>;

public:
	flat_map_t() : _alloc(), _map(&_alloc)
	{}
	~flat_map_t() {}

private:
	_AllocType _alloc;
	_MapType _map;

};

} // net
} // pmr
