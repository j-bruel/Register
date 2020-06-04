//!
//! @file GetAbsolutePath.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/reg/GetAbsolutePath.hpp"
#include "jbr/reg/exception.hpp"
#include <filesystem>

namespace jbr::reg
{
    std::string     getAbsolutePath(const std::string &relativePath)
    {
        if (relativePath.empty())
            throw jbr::reg::exception("Relative input string must not be empty.");

        std::error_code ec;
        std::string     absolutePath(std::filesystem::canonical(std::filesystem::path(relativePath), ec).string());

        if (ec)
            throw jbr::reg::exception("Impossible to extract the absolute path from : " + relativePath + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message() + ".");
        return (absolutePath);
    }

}
