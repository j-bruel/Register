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

    jbr::Register   Manager::create(const char *path, const std::optional<jbr::reg::Rights> &rights) noexcept(false)
    {
        if (exist(path))
            throw jbr::reg::exception("The register '" + std::string(path) + "' already exist. You must remove it before create it or open it.");

        jbr::Register   reg = std::make_unique<jbr::reg::Instance>(path);

        reg->createHeader(rights);
        return (reg);
    }

    jbr::Register   Manager::open(const char *path) noexcept(false)
    {
        if (!exist(path))
            throw jbr::reg::exception("The register '" + std::string(path == nullptr ? "" : path) + "' does not exist. You must create it before.");

        jbr::Register   reg = std::make_unique<jbr::reg::Instance>(path);

        if (!reg->isOpenable())
            throw jbr::reg::exception("The register '" + std::string(path) + "' is not openable. Please check the register rights, read and open must be allowed.");
        return (reg);
    }

    bool    Manager::exist(const char *path) noexcept
    {
        if (path == nullptr || !path[0])
            return (false);
        return (std::filesystem::exists(path));
    }

    void    Manager::destroy(jbr::Register &reg) noexcept(false)
    {
        const std::string &regPath = reg->localization();

        if (!reg->isDestroyable())
            throw jbr::reg::exception("The register '" + regPath + "' is not destroyable. Please check the register rights, read and destroy must be allow.");
        std::filesystem::remove(regPath);
    }
    
}
