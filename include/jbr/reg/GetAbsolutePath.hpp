//!
//! @file GetFullPath.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_GETABSOLUTEPATH_HPP
# define JBR_CREGISTER_GETABSOLUTEPATH_HPP

# include <string>
# include "jbr/reg/exception.hpp"
# include <filesystem>

//!
//! @namespace jbr
//!
namespace jbr::reg
{

    //!
    //! @static
    //! @brief Extract absolute path from relative path.
    //! @param relativePath Relative reference path.
    //! @return Absolute path generate from relative input path.
    //!
    static const std::string    getAbsolutePath(const std::string &relativePath)
    {
        if (relativePath.empty())
            throw jbr::reg::exception("Relative input string must not be empty.");
        return (std::filesystem::absolute(relativePath).string());
    }

}

#endif //JBR_CREGISTER_GETABSOLUTEPATH_HPP
