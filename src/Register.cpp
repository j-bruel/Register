//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/Register.hpp"
#include "jbr/reg/exception.hpp"
#include <tinyxml2.h>
#include <fstream>
#include <iostream>

namespace jbr
{
    void    Register::create(const std::string &path) const
    {
        if (path.empty())
            throw jbr::reg::exception("To create a register the path must not be empty.");
        if (exist(path))
            throw jbr::reg::exception("The register " + path + " already exist. You must remove it before create it or open it.");
        createHeader(path);
    }

    void    Register::open(const std::string &path) const
    {
        if (path.empty())
            throw jbr::reg::exception("To open a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("The register " + path + " does not exist. You must create it before.");
    }

    bool    Register::exist(const std::string &path) const noexcept
    {
        if (path.empty())
            return (false);

        std::error_code     ec;

        return (std::filesystem::exists(path, ec));
    }

    void    Register::destroy(const std::string &path) const
    {
        if (path.empty())
            throw jbr::reg::exception("To destroy a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to destroy a not existing register : " + path + ".");

        std::error_code     ec;

        if (!std::filesystem::remove(path, ec))
            throw jbr::reg::exception("Impossible to destroy this next register : " + path + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message());
    }

    void    Register::createHeader(const std::string &path) const
    {
        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLNode       *nodeReg = reg.NewElement("register");
        tinyxml2::XMLNode       *nodeHeader = reg.NewElement("header");
        tinyxml2::XMLNode       *nodeBody = reg.NewElement("body");
        tinyxml2::XMLElement    *version = reg.NewElement("version");
        tinyxml2::XMLNode       *nodeRights = reg.NewElement("rights");
        tinyxml2::XMLElement    *read = reg.NewElement("read");
        tinyxml2::XMLElement    *write = reg.NewElement("write");

        reg.InsertFirstChild(nodeReg);
        nodeReg->InsertFirstChild(nodeHeader);
        nodeReg->InsertAfterChild(nodeHeader, nodeBody);
        version->SetText(1.0);
        nodeHeader->InsertEndChild(version);
        nodeHeader->InsertAfterChild(version, nodeRights);
        read->SetText(true);
        write->SetText(true);
        nodeRights->InsertFirstChild(read);
        nodeRights->InsertAfterChild(read, write);

        tinyxml2::XMLError  err = reg.SaveFile(path.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Parsing error, error code : " + std::to_string(err));
    }

}