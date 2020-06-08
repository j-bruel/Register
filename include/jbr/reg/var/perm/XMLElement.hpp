//!
//! @file XMLElement.hpp
//! @author jbruel
//! @date 08/06/2020
//!

#ifndef JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP
# define JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP

# include <jbr/reg/var/perm/Rights.hpp>
# include <jbr/reg/exception.hpp>
# include <tinyxml2.h>

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
                                                            mRemoveElement(reg->NewElement("remove")) { checkValidity(); }

        //!
        //! @brief Initialize all text field of xml elements.
        //! @param rights Rights used to set the text field.
        //!
        void setText(const jbr::reg::var::perm::Rights &rights) const noexcept(false);

        //!
        //! @brief Check all xml element validity.
        //! @throw Raise if one of the xml element is null.
        //!
        void checkValidity() const noexcept(false);
    };

}

#endif //JBR_CREGISTER_VARIABLE_PERMISSION_XMLELEMENT_HPP
