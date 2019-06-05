//!
//! @file main.cpp
//! @author jbruel
//! @date 29/04/19
//!

#include <jbr/Register.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    jbr::Register   reg;

    reg.create("./sample.reg");
    std::cout << "Is my register existing ? " << reg.exist("./sample.reg") << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    return (EXIT_SUCCESS);
}