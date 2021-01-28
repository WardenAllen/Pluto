#pragma once

/*
 * @author WardenAllen
 * @date   2020/10/26 19:57:12
 * @brief  Disable copy / move constructor macro.
 */

namespace pluto
{
namespace util
{

#define NON_COPYABLE_NOR_MOVABLE(classname)                 \
  public:                                                   \
    classname (const classname &) = delete;                 \
    classname &operator= (const classname &) = delete;      \
    classname (classname &&) = delete;                      \
    classname &operator= (classname &&) = delete;

} // util
} // pluto
