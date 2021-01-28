#pragma once

/*
 * @author WardenAllen
 * @date   2020/10/26 19:57:12
 * @brief  Singleton helper template.
 */

namespace pluto
{
namespace util
{

/* 1. c++11 style template. */

template <class T>
class singleton_t
{
protected:
	singleton_t() = default;
	virtual ~singleton_t() = default;

private:
	singleton_t(const T& other) = delete;

public:
	static T* instance() {
		static T instance;
		return &instance;
	}
};

/* How to use: */

/*
 * class Derived : public singleton_t<Test> 
 * {
 * public:
 *     Derived() {}
 *     ~Derived() {}
 * };
 */

/* 
 * 2. As it's better not to call DERIVED CONSTRUCTOR in BASE CONSTRUCTOR,
 * and the code above CANNOT prevent to call constructor directly,
 * maybe the following code is better. 
 */

/*
 * # define SINGLETON(class)		\
 *	 static class* Instance() {		\
 *     static class instance;		\
 *     return &instance;			\
 *   }
 * 
 * class Derived
 * {
 * private:
 *     Derived() {}
 *     ~Derived() {}
 * 
 * public:
 *     SINGLETON(Derived)
 * };
 */

/* 3. (template can use different contructors) */

/*
 * template <typename T>
 * class singleton_t
 * {
 * protected:
 * 	static T* _instance;
 * 
 * public:
 * 	singleton_t(void) {
 * 		_instance = static_cast<T*>(this);
 * 	}
 * 	~singleton_t(void) { assert(_instance);  _instance = 0; }
 * 
 * public:
 * 	static T& instance_ref(void) { assert(_instance); return (*_instance); }
 * 	static T* instance(void) { return _instance; }
 * };
 * 
 * #define SINGLETON_INIT( TYPE )	\
 * template <>	TYPE * singleton_t< TYPE >::_instance = 0;
 * 
 * class A : public singleton_t<A>
 * {
 * public:
 * 	A(int i) : _i(i) {}
 * private:
 * 	int _i;
 * };
 * 
 * A a(1);
 *
 * SINGLETON_INIT(A) // put this line in cpp file.
 *
 */



} // util
} // pluto
