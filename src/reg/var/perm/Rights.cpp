//!
//! @file jbr/reg/var/perm/Rights.cpp
//! @author jbruel
//! @date 30/07/19
//!

#include "jbr/reg/var/perm/Rights.hpp"

namespace jbr::reg::var::perm
{

    Rights  &Rights::operator=(const Rights &rights)
    {
        mRead = rights.mRead;
        mWrite = rights.mWrite;
        mUpdate = rights.mUpdate;
        mRename = rights.mRename;
        mCopy = rights.mCopy;
        mRemove = rights.mRemove;
        return (*this);
    }

}
