//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/Register.hpp"
#include "jbr/reg/GetAbsolutePath.hpp"
#include <iostream>

namespace jbr
{
    void    Register::create(const std::string &path)
    {
        if (path.empty())
            throw jbr::reg::exception("To create a register the path must not be empty.");

        const std::string   fullPath = jbr::reg::getAbsolutePath("./toto.txt");

        std::cout << fullPath << std::endl;
    }
}