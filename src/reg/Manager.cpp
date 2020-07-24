//!
//! @file Manager.cpp
//! @author jbruel
//! @date 13/07/20
//!

#include "jbr/reg/Manager.hpp"
#include "jbr/reg/exception.hpp"
#include <filesystem>

namespace jbr::reg
{

    jbr::Register   Manager::create(const std::string &path, const std::optional<jbr::reg::Rights> &rights) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To create a register the path must not be empty.");
        if (exist(path))
            throw jbr::reg::exception("The register " + path + " already exist. You must remove it before create it or open it.");

        jbr::Register   reg = std::make_unique<jbr::reg::Instance>(path.c_str());

        reg->createHeader(rights);
        return (reg);
    }

    jbr::Register   Manager::open(const std::string &path) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To open a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("The register " + path + " does not exist. You must create it before.");

        jbr::Register   reg = std::make_unique<jbr::reg::Instance>(path.c_str());

        if (!reg->isOpenable())
            throw jbr::reg::exception("The register " + path + " is not openable. Please check the register rights, read and open must be allowed.");
        return (reg);
    }

    bool    Manager::exist(const std::string &path) noexcept
    {
        if (path.empty())
            return (false);
        return (std::filesystem::exists(path));
    }

    void    Manager::destroy(jbr::Register &reg) noexcept(false)
    {
        const std::string &regPath = reg->localization();

        if (!reg->isDestroyable())
            throw jbr::reg::exception("The register " + regPath + " is not destroyable. Please check the register rights, read and destroy must be allow.");
        std::filesystem::remove(regPath);
    }

}
