//!
//! @file jbr/reg/var/perm/Rights.hpp
//! @author jbruel
//! @date 30/07/19
//!

#ifndef JBR_CREGISTER_REGISTER_VAR_PERM_RIGHTS_HPP
# define JBR_CREGISTER_REGISTER_VAR_PERM_RIGHTS_HPP

//!
//! @namespace jbr::reg::var::perm
//!
namespace jbr::reg::var::perm
{
    //!
    //! @struct Rights
    //! @brief All variables rights.
    //!
    struct Rights final
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
        //!
        //! @brief Structure initializer with custom rights initialization.
        //! @param rd Reading rights.
        //! @param wr Writing rights.
        //! @param up Allow to update a variable.
        //! @param rn Allow to rename a variable.
        //! @param cp Allow to copy a variable.
        //! @param rm Allow to remove a variable.
        //!
        Rights(bool rd, bool wr, bool up, bool rn, bool cp, bool rm) :  mRead(rd), mWrite(wr), mUpdate(up),
                                                                        mRename(rn), mCopy(cp), mRemove(rm) {}
        //!
        //! @brief Copy constructor. Trivial declaration, using equal overload operator.
        //!
        Rights(const Rights &) = default;
        //!
        //! @brief Equal operator overload.
        //! @param rights Rights to apply to the new register.
        //! @return New rights data structure according original rights.
        //!
        Rights  &operator=(const Rights &rights);
        //!
        //! @brief Default destructor.
        //!
        ~Rights() = default;
    };
}

#endif //JBR_CREGISTER_REGISTER_VAR_PERM_RIGHTS_HPP
