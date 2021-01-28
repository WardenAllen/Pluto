#pragma once

/*
 * @author WardenAllen
 * @date   2020/08/31 20:05:20
 * @brief
 */

#ifdef __cplusplus 
#undef __cplusplus 
#endif // __cplusplus 

#define __cplusplus 202002

namespace pluto
{

#define PLUTO_NON_COPYABLE_NOR_MOVABLE(classname)                       \
    public:                                                             \
        classname (const classname &) = delete;                         \
        classname &operator= (const classname &) = delete;              \
        classname (classname &&) = delete;                              \
        classname &operator= (classname &&) = delete;

}