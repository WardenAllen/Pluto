#pragma once

/*
 * @author WardenAllen
 * @date   2020/10/23 19:01:43
 * @brief  
 */

#include <string>

namespace pluto
{
namespace base
{

class printable
{
public:
	printable() = default;
	virtual ~printable() = default;

public:
	virtual std::string to_string() = 0;
};

} // base
} // pluto
