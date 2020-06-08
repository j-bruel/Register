//!
//! @file XMLElement.cpp
//! @author jbruel
//! @date 08/06/2020
//!

#include <jbr/reg/var/perm/XMLElement.hpp>
#include <jbr/reg/exception.hpp>

namespace jbr::reg::var::perm
{

    void    XMLElement::setText(const jbr::reg::var::perm::Rights &rights) const noexcept(false)
    {
        checkValidity();
        mReadElement->SetText(rights.mRead);
        mWriteElement->SetText(rights.mWrite);
        mUpdateElement->SetText(rights.mUpdate);
        mRenameElement->SetText(rights.mCopy);
        mCopyElement->SetText(rights.mCopy);
        mRemoveElement->SetText(rights.mRemove);
    }

    void    XMLElement::checkValidity() const noexcept(false)
    {
        if (mReadElement == nullptr || mWriteElement == nullptr || mUpdateElement == nullptr ||
            mRenameElement == nullptr || mCopyElement == nullptr || mRemoveElement == nullptr)
            throw jbr::reg::exception("Error while saving the variable rights content, null pointer detected.");
    }

}
