//!
//! @file Rights.hpp
//! @author jbruel
//! @date 02/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_PERM_RIGHTS_HPP
# define JBR_CREGISTER_REGISTER_PERM_RIGHTS_HPP

# include <jbr/reg/Permission.hpp>

//!
//! @namespace jbr::reg::perm
//!
namespace jbr::reg::perm
{
    //!
    //! @struct Rights
    //! @brief All register rights.
    //!
    struct Rights final : public jbr::reg::Permission
    {
        bool    mOpen; //!< Allow to open a register.
        bool    mCopy; //!< Allow to copy a register.
        bool    mMove; //!< Allow to move a register.
        bool    mDestroy; //!< Allow to destroy a register.

        //!
        //! @brief Structure initializer. All rights are true by default.
        //!
        Rights() : jbr::reg::Permission(), mOpen(true), mCopy(true), mMove(true), mDestroy(true) {}
        //!
        //! @brief Structure initializer with custom rights initialization.
        //! @param rd Reading rights.
        //! @param wr Writing rights.
        //! @param op Allow to open a register.
        //! @param cp Allow to copy a register.
        //! @param mv Allow to move a register.
        //! @param ds Allow to destroy a register.
        //!
        explicit Rights(bool rd, bool wr, bool op, bool cp, bool mv, bool ds) : jbr::reg::Permission(rd, wr), mOpen(op),
                                                                                mCopy(cp), mMove(mv), mDestroy(ds) {}
    };
}

#endif //JBR_CREGISTER_REGISTER_PERM_RIGHTS_HPP
