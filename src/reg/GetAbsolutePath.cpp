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

        std::error_code     ec;
        const std::string   absolutePath(std::filesystem::absolute(std::filesystem::path(relativePath), ec));

        if (ec)
            throw jbr::reg::exception("Impossible to extract the absolute path from : " + relativePath + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message());
        return (absolutePath);
    }

}