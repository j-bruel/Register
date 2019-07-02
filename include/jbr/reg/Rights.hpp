//!
//! @file Rights.hpp
//! @author jbruel
//! @date 02/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_RIGHTS_HPP
# define JBR_CREGISTER_REGISTER_RIGHTS_HPP

//!
//! @namespace jbr::reg
//!
namespace jbr::reg
{
    //!
    //! @struct Rights
    //! @brief All register rights.
    //!
    struct Rights
    {
        bool    mRead; //!< Reading rights.
        bool    mWrite; //!< Writing rights.
        bool    mOpen; //!< Allow to open a register.
        bool    mCopy; //!< Allow to copy a register.
        bool    mMove; //!< Allow to move a register.
        bool    mDestroy; //!< Allow to destroy a register.

        //!
        //! @brief Structure initializer. All rights are true by default.
        //!
        Rights() : mRead(true), mWrite(true), mOpen(true), mCopy(true), mMove(true), mDestroy(true) {}
    };
}

#endif //JBR_CREGISTER_REGISTER_RIGHTS_HPP
