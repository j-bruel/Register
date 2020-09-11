//!
//! @file Permission.hpp
//! @author jbruel
//! @date 30/07/20
//!

#ifndef JBR_CREGISTER_REGISTER_PERMISSION_HPP
# define JBR_CREGISTER_REGISTER_PERMISSION_HPP

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{

    //!
    //! @class Permission
    //! @brief Abstract structure for sub-permission (rights handling).
    //!
    struct Permission
    {
        bool    mRead; //!< Reading rights.
        bool    mWrite; //!< Writing rights.

        //!
        //! @brief Structure initializer. All rights are true by default.
        //!
        Permission() : mRead(true), mWrite(true) {}
        //!
        //! @brief Structure initializer with custom rights initialization.
        //! @param rd Reading rights.
        //! @param wr Writing rights.
        //!
        Permission(bool rd, bool wr) :  mRead(rd), mWrite(wr) {}
    };

}

#endif //JBR_CREGISTER_REGISTER_PERMISSION_HPP
