//!
//! @file XMLElement.hpp
//! @author jbruel
//! @date 08/06/2020
//!

#ifndef JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP
# define JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP

# include <jbr/reg/exception.hpp>

//!
//! @namespace jbr::reg::var::perm
//!
namespace jbr::reg::var::perm
{

    //!
    //! @struct XMLElement
    //! @brief All variables permission into a xml element structure.
    //!
    struct XMLElement final
    {
        tinyxml2::XMLElement    *mReadElement; //!< Reading rights.
        tinyxml2::XMLElement    *mWriteElement; //!< Writing rights.
        tinyxml2::XMLElement    *mUpdateElement; //!< Allow to update a variable.
        tinyxml2::XMLElement    *mRenameElement; //!< Allow to rename a variable.
        tinyxml2::XMLElement    *mCopyElement; //!< Allow to copy a variable.
        tinyxml2::XMLElement    *mRemoveElement; //!< Allow to remove a variable.

        //!
        //! @brief Default constructor.
        //! @warning Not usable.
        //!
        XMLElement() = delete;

        //!
        //! @brief Build all permissions elements according register xml document.
        //! @param reg XML document object.
        //!
        explicit XMLElement(tinyxml2::XMLDocument *reg) :   mReadElement(reg->NewElement("read")),
                                                            mWriteElement(reg->NewElement("write")),
                                                            mUpdateElement(reg->NewElement("update")),
                                                            mRenameElement(reg->NewElement("rename")),
                                                            mCopyElement(reg->NewElement("copy")),
                                                            mRemoveElement(reg->NewElement("remove"))
        {
            if (mReadElement == nullptr || mWriteElement == nullptr || mUpdateElement == nullptr ||
                mRenameElement == nullptr || mCopyElement == nullptr || mRemoveElement == nullptr)
                throw jbr::reg::exception("Error while saving the variable rights content, null pointer detected.");
        }
    };

}

#endif //JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP
