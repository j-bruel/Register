//!
//! @file main.cpp
//! @author jbruel
//! @date 29/04/19
//!

#include "jbr/reg/HelloWorld.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    jbr::reg::HelloWorld    hw;

    std::cout << hw.hello() << std::endl;
    std::cout << hw.world() << std::endl;
    std::cout << hw.generateRandomNumber() << std::endl;
    std::cout << hw.headerFunction(3) << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    return 0;
}