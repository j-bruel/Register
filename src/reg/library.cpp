#include "jbr/library.hpp"

#include <iostream>

extern "C"
{
EXPORTED inline void hello()
{
    std::cout << "Hello, World!" << std::endl;
}

}

void hello4()
{
    std::cout << "Hello, World5!" << std::endl;
}