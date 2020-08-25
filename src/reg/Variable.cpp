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

    std::string Variable::key() const noexcept(false)
    {
        if (!mRights.mRead)
            throw jbr::reg::exception("Impossible to read a register variable, right must be set to true.");
        return (mName);
    }

    std::string Variable::read() const noexcept(false)
    {
        if (!mRights.mRead)
            throw jbr::reg::exception("Impossible to read a register variable, right must be set to true.");
        return (mValue);
    }

    void         Variable::update(std::string &&value) noexcept(false)
    {
        if (!mRights.mWrite || !mRights.mUpdate)
            throw jbr::reg::exception("Impossible to update a register variable, the 'write' and 'update' rights must be set to true.");
        mValue = value;
    }

    void        Variable::rename(std::string &&name) noexcept(false)
    {
        if (!mRights.mRead || !mRights.mUpdate || !mRights.mRename)
            throw jbr::reg::exception("Impossible to rename a register variable, the 'read', 'update' and 'rename' rights must be set to true.");
        if (name.empty())
            throw jbr::reg::exception("Impossible to rename a register variable to a empty value.");
        mName = name;
    }

}
