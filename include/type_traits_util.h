#pragma once

/*
 * @author WardenAllen
 * @date   2020/10/22 16:01:57
 * @brief  
 */

#include <type_traits>
#include <chrono>
#include <map>
#include <unordered_map>
#include <string>

namespace pluto
{
namespace util
{

/* check whether it's a single element container. */

template <class>
struct is_single_element_container : public std::true_type {};

template <class _K, class _V>
struct is_single_element_container<std::unordered_map<_K, _V>> :
	public std::false_type {};

template <class _K, class _V>
struct is_single_element_container<std::map<_K, _V>> :
	public std::false_type {};


/* remove non-pointer type's const, volatile and reference */

template <class _Tp>
struct remove_cvr {
	using type = typename std::remove_cv<
		typename std::remove_reference<_Tp>::type
	>::type;
};

/* remove pointer type's const, volatile and reference */

template <class _Tp>
struct remove_cvr_p {
	using type = typename remove_cvr<_Tp>::type;
};

template <class _Tp>
struct remove_cvr_p<_Tp*> {
	using type = typename std::add_pointer<
		typename remove_cvr<_Tp>::type>::type;
};


/* check whether it's a basic string (char *, char[]...). */

template <class T>
struct is_basic_string : std::integral_constant < bool,
	std::is_same<typename std::decay<
	typename remove_cvr_p<T>::type>::type, char*>::value> 
{};

template <class T>
struct is_string : 
	std::integral_constant <bool,
	std::is_same<typename remove_cvr<T>::type, std::string>::value ||
	std::is_same<typename remove_cvr<T>::type, std::wstring>::value>
{};

template <class T>
struct is_parse_string :
	std::integral_constant <bool,
	pluto::util::is_string<T>::value || std::is_arithmetic<T>::value ||
	std::is_same<typename remove_cvr<T>::type, char *>::value>
{};


/* parse type to string. */

template <class T,
	typename std::enable_if<is_string<T>::value, int>::type = 0>
	std::string parse_string(T t) { return static_cast<std::string>(t); }

template <class T,
	typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
	std::string parse_string(T t) { return std::to_string(t); }

template <class T,
	typename std::enable_if<is_basic_string<T>::value, int>::type = 0>
	std::string parse_string(T t) { return std::string(t); }

/* traits std::chrono::duration's unit name. */
template <class Unit>
struct chrono_trait_t {
	inline static constexpr char unit_name[] = "??";
	static constexpr int den = 1;
};

template <>
struct chrono_trait_t<std::chrono::nanoseconds> {
	inline static constexpr char unit_name[] = "ns";
	static constexpr int den = 1;
};

template <>
struct chrono_trait_t<std::chrono::microseconds> {
	inline static constexpr char unit_name[] = "us";
	static constexpr int den = 1000;
};

template <>
struct chrono_trait_t<std::chrono::milliseconds> {
	inline static constexpr char unit_name[] = "ms";
	static constexpr int den = 1000 * 1000;
};

template <>
struct chrono_trait_t<std::chrono::seconds> {
	inline static constexpr char unit_name[] = "sec";
	static constexpr int den = 1000 * 1000 * 1000;
};

/**
 * Warning: 
 *    the follow 2 define cannot judge 'template member 
 *    functions'!
 */

#define DECLARE_HAS_MEMBER_VARIABLE(v)						\
	template <typename T>									\
	struct has_member_##v									\
	{														\
		template<typename U>								\
		static void check(typename std::enable_if<			\
			!std::is_member_function_pointer<				\
			decltype(&U::Test)>::value, int>::type = 0);	\
															\
		template<typename U>								\
		static int check(...);								\
															\
		static constexpr bool value = std::is_void<			\
			decltype(check<T>(0))>::value;					\
	};

#define DECLARE_HAS_MEMBER_MEMBER_FUNC(v)					\
	template <typename T>									\
	struct has_member_##v									\
	{														\
		template<typename U>								\
		static void check(typename std::enable_if<			\
			std::is_member_function_pointer<				\
			decltype(&U::Test)>::value, int>::type = 0);	\
															\
		template<typename U>								\
		static int check(...);								\
															\
		static constexpr bool value = std::is_void<			\
			decltype(check<T>(0))>::value;					\
	};

} // util
} // pluto
