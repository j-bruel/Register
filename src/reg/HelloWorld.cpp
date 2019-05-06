//!
//! @file reg/hello_world.cpp
//! @author jbruel
//! @date 29/04/19
//!

#include "jbr/reg/HelloWorld.hpp"

namespace jbr
{
namespace reg
{

    HelloWorld::HelloWorld() : mHello("Hello"), mWorld("World") {}

    int HelloWorld::headerFunction(int number) const
    {
        if (number % 2 == 0)
            return (number / 2);
        return (3);
    }

}
}