//!
//! @file GetAbsolutePath.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/reg/GetAbsolutePath.hpp"
#include "jbr/reg/exception.hpp"
#include <filesystem>
#include <iostream>

namespace jbr::reg
{
    const std::string   getAbsolutePath(const std::string &relativePath)
    {
        if (relativePath.empty())
            throw jbr::reg::exception("Relative input string must not be empty.");
        return (std::filesystem::absolute(std::filesystem::path(relativePath)));
    }

}