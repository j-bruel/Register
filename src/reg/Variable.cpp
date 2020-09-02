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

    const char   *Variable::key() const noexcept(false)
    {
        if (!isReadable())
            throw jbr::reg::exception("Impossible to read a register variable, right must be set to true.");
        return (mName.c_str());
    }

    const char   *Variable::read() const noexcept(false)
    {
        if (!isReadable())
            throw jbr::reg::exception("Impossible to read a register variable, right must be set to true.");
        return (mValue.c_str());
    }

    void         Variable::update(std::string &&value) noexcept(false)
    {
        if (!isUpdatable())
            throw jbr::reg::exception("Impossible to update a register variable, the 'write' and 'update' rights must be set to true.");
        mValue = value;
    }

    void        Variable::rename(std::string &&name) noexcept(false)
    {
        if (!isRenamable())
            throw jbr::reg::exception("Impossible to rename a register variable, the 'write', 'update' and 'rename' rights must be set to true.");
        if (name.empty())
            throw jbr::reg::exception("Impossible to rename a register variable to a empty value.");
        mName = name;
    }

    void        Variable::reaccess(const jbr::reg::var::perm::Rights &rights) noexcept(false)
    {
        if (!isUpdatable())
            throw jbr::reg::exception("Impossible to reaccess a register variable, the 'read', 'write' and 'update' rights must be set to true.");
        mRights = rights;
    }

}
