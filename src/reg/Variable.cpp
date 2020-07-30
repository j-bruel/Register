//!
//! @file Variable.cpp
//! @author jbruel
//! @date 30/07/19
//!

#include "jbr/reg/Variable.hpp"

namespace jbr::reg
{
    Variable::Variable(std::string &&name, std::string &&value, const std::optional<jbr::reg::var::perm::Rights> &rights) : mValue(value)
    {
        if (name.empty())
            throw jbr::reg::exception("Impossible to set a empty register variable.");
        mName = name;
        if (rights != std::nullopt)
            mRights = rights.value();
    }

    void        Variable::rename(std::string &&name) noexcept(false)
    {
        if (name.empty())
            throw jbr::reg::exception("Impossible to rename a register variable to a empty value.");
        mName = name;
    }

}
