//!
//! @file Variable.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include "jbr/reg/exception.hpp"
#include "jbr/reg/Variable.hpp"
#include <tinyxml2.h>

namespace jbr::reg
{
    Variable::Variable(const std::string &registerPath) : mPath(registerPath)
    {
        if (mPath.empty())
            throw jbr::reg::exception("Register variable can not be build according a empty register path.");
        if (!exist(mPath))
            throw jbr::reg::exception("Register variable can not be build according a not existing register : " + mPath + '.');
    }

/*    void    Variable::operator=(const std::string &value) const
    {
    }*/
}