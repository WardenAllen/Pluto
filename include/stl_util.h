#pragma once

/*
 * @author WardenAllen
 * @date   2020/09/02 11:53:11
 * @brief  
 */

#include <iostream>
#include <map>
#include <unordered_map>

#include "define.h"
#include "type_traits_util.h"

namespace pluto
{
namespace util
{

/* first way */
//template <class T>
//typename std::enable_if<is_single_element_container<T>::value, void>::type
//test() { std::cout << "do something when is single!" << std::endl; }
//
//template <class T>
//typename std::enable_if<!is_single_element_container<T>::value, void>::type
//test() { std::cout << "do something when is not single!" << std::endl; }

/* second way */
template < class T,
	typename std::enable_if<is_single_element_container<T>::value, int>::type = 0>
	void test() { std::cout << "do something when is single!" << std::endl; }

template < class T,
	typename std::enable_if<!is_single_element_container<T>::value, int>::type = 0>
	void test() { std::cout << "do something when is not single!" << std::endl; }

#if __cplusplus > 201703L
#define STL_LOOP_DELETE(c, f) std::erase_if(c, f)
#else
/* can be used for vector, set, list, map, unordered_map */
#define STL_LOOP_DELETE(c, f)					\
	for (auto _it = c.begin(), _last = c.end(); \
		_it != _last;) {						\
		if (f(*_it)) _it = c.erase(_it);		\
		else ++_it;								\
	}
#endif

// static const auto DEFAULT_DELETE_FUNC = [](const auto p) { delete* p; p = nullptr; };

template <class TP,
	template <class ELEM,
	class ALLOC = std::allocator<ELEM>> class TC>
void stl_clear(TC<TP, std::allocator<TP>>& c) {
	for (auto& it : c)
	{
		delete it;
		it = nullptr;
	}
	c.clear();
}

template<class T1, class T2, template <
	class _Kty,
	class _Ty,
	class _Pr = std::less<_Kty>,
	class _Alloc = std::allocator<std::pair<const _Kty, _Ty>>> 
	class M>
void stl_clear(M<T1, T2, std::less<T1>,
		std::allocator<std::pair<const T1, T2>>>& c) {
	for (auto& it : c)
	{
		delete it.second;
		it.second = nullptr;
	}
	c.clear();
}


/**
* @brief  like map.try_emplace(), insert pair into multimap or 
*		  unordered_* stl-containers.
*/
template <typename _C, typename _K, typename... _Args>
auto try_emplace(_C& c, _K&& key, _Args&&... args) {
	return c.emplace(std::piecewise_construct,
		std::forward_as_tuple(std::forward<_K>(key)),
		std::forward_as_tuple(std::forward<_Args>(args)...));
}

} // time
} // pluto