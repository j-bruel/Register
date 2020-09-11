//!
//! @file main.cpp
//! @author jbruel
//! @date 29/04/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    jbr::reg::Rights    rights;

    rights.mCopy = false;
    rights.mMove = false;
    try {
        jbr::Register       reg = jbr::reg::Manager::create("./sample.reg", rights);
    }
    catch (jbr::reg::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    return (EXIT_SUCCESS);
}
