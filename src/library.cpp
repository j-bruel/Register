#include "jbr/library.h"

#include <iostream>

extern "C"
{
EXPORTED inline void hello()
{
    std::cout << "Hello, World!" << std::endl;
}
}