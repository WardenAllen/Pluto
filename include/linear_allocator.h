#pragma once

/*
 * @author WardenAllen
 * @date   2020/12/03 16:25:05
 * @brief  
 */

#include <memory_resource>

namespace pluto
{
namespace pmr
{

template <class _Type>
class linear_allocator_t 
	: public std::pmr::memory_resource
{
public:
	linear_allocator_t() {}
	~linear_allocator_t() {}

private:
	virtual void* do_allocate(size_t __bytes, size_t __alignment)
	{
		return operator new (__bytes);
	}

	virtual void do_deallocate(void* __p, size_t __bytes, size_t __alignment)
	{
		free(__p);
	}

	virtual bool do_is_equal(const memory_resource& __other) const noexcept
	{
		return true;
	}
};

} // net
} // pmr
