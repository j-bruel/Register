#include <iostream>
#include "jbr/library.h"
#include "jbr/reg/HelloWorld.hpp"

int main()
{
    jbr::reg::HelloWorld    hw;

    std::cout << hw.hello() << std::endl;
    while (true);
    return 0;
}