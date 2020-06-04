//!
//! @file GetAbsolutePath.hpp
//! @author jbruel
//! @date 20/05/19
//!

#ifndef JBR_CREGISTER_GETABSOLUTEPATH_HPP
# define JBR_CREGISTER_GETABSOLUTEPATH_HPP

# include <string>

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @brief Extract absolute path from relative path.
    //! @param relativePath Relative reference path.
    //! @return Absolute path generate from relative input path.
    //!
    [[nodiscard]] std::string    getAbsolutePath(const std::string &relativePath) noexcept(false);

}

#endif //JBR_CREGISTER_GETABSOLUTEPATH_HPP
