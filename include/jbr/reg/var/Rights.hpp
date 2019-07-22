//!
//! @file Rights.hpp
//! @author jbruel
//! @date 22/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_VARIABLES_RIGHTS_HPP
# define JBR_CREGISTER_REGISTER_VARIABLES_RIGHTS_HPP

//!
//! @namespace jbr::reg::var
//!
namespace jbr::reg::var
{
    //!
    //! @struct Rights
    //! @brief All variables rights.
    //!
    struct Rights
    {
        bool    mRead; //!< Reading rights.
        bool    mWrite; //!< Writing rights.
        bool    mUpdate; //!< Allow to update a variable.
        bool    mRename; //!< Allow to rename a variable.
        bool    mCopy; //!< Allow to copy a variable.
        bool    mRemove; //!< Allow to remove a variable.

        //!
        //! @brief Structure initializer. All rights are true by default.
        //!
        Rights() : mRead(true), mWrite(true), mUpdate(true), mRename(true), mCopy(true), mRemove(true) {}
    };
}

#endif //JBR_CREGISTER_REGISTER_VARIABLES_RIGHTS_HPP
