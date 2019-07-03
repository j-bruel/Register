//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/Register.hpp"
#include "jbr/reg/exception.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace jbr
{
    void    Register::create(const std::string &path, const std::optional<jbr::reg::Rights> &rights) const
    {
        if (path.empty())
            throw jbr::reg::exception("To create a register the path must not be empty.");
        if (exist(path))
            throw jbr::reg::exception("The register " + path + " already exist. You must remove it before create it or open it.");
        createHeader(path, rights);
    }

    void    Register::open(const std::string &path)
    {
        if (path.empty())
            throw jbr::reg::exception("To open a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("The register " + path + " does not exist. You must create it before.");
        verify(path);
        if (!isOpenable())
            throw jbr::reg::exception("The register " + path + " is not openable. Please check the register rights, read and open must be allowed.");
    }

    bool    Register::exist(const std::string &path) const noexcept
    {
        if (path.empty())
            return (false);

        std::error_code     ec;

        return (std::filesystem::exists(path, ec));
    }

    void    Register::verify(const std::string &path)
    {
        if (path.empty())
            throw jbr::reg::exception("To check if a register is corrupt the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to check the corruption status of a not existing register : " + path + '.');

        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLError      err = reg.LoadFile(path.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Parsing error while loading the register file, error code : " + std::to_string(err) + '.');

        tinyxml2::XMLNode       *nodeReg = reg.FirstChildElement("register");

        if (nodeReg == nullptr)
            throw jbr::reg::exception("Register corrupted. Did not find register node, the format is corrupt.");

        tinyxml2::XMLNode       *nodeHeader = nodeReg->FirstChildElement("header");

        if (nodeHeader == nullptr)
            throw jbr::reg::exception("Register corrupted. Did not find header node, the format is corrupt.");

        tinyxml2::XMLElement    *version = nodeHeader->FirstChildElement("version");

        if (version == nullptr)
            throw jbr::reg::exception("Register corrupted. Did not find version field from register/header nodes, mandatory field missing.");

        double  versionValue;

        err = version->QueryDoubleText(&versionValue);
        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Register corrupted. Field version from register/header nodes not set or invalid, error code : " + std::to_string(err) + '.');
        verifyRights(nodeHeader);

        tinyxml2::XMLElement    *bodyNode = nodeReg->FirstChildElement("body");

        if (bodyNode == nullptr)
            throw jbr::reg::exception("Register corrupted. Did not find body node, the format is corrupt.");
    }

    void    Register::copy(const std::string &pathFrom, const std::string &pathTo)
    {
        if (pathFrom.empty())
            throw jbr::reg::exception("To copy a register the copied register path must not be empty.");
        if (pathTo.empty())
            throw jbr::reg::exception("To copy a register the new register path must not be empty.");
        if (!exist(pathFrom))
            throw jbr::reg::exception("Impossible to copy a not existing register : " + pathFrom + ".");
        if (exist(pathTo))
            throw jbr::reg::exception("Impossible to copy the register " + pathFrom + ". Target path already have a register existing : " + pathTo + ".");
        verify(pathFrom);
        if (!isCopyable())
            throw jbr::reg::exception("The register " + pathFrom + " is not copyable. Please check the register rights, read and copy must be allow.");

        std::error_code     ec;

        if (!std::filesystem::copy_file(pathFrom, pathTo, ec))
            throw jbr::reg::exception("Impossible to copy this next register : " + pathFrom + " to : " + pathTo + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message() + '.');
    }

    void    Register::move(const std::string &pathOld, const std::string &pathNew)
    {
        if (pathOld.empty())
            throw jbr::reg::exception("To move a register the reference path must not be empty.");
        if (pathNew.empty())
            throw jbr::reg::exception("To move a register the destination path must not be empty.");
        if (!exist(pathOld))
            throw jbr::reg::exception("Impossible to move a not existing register : " + pathOld + ".");
        if (exist(pathNew))
            throw jbr::reg::exception("Impossible to move the register " + pathOld + ". Target path already have a register existing : " + pathNew + ".");
        verify(pathOld);
        if (!isMovable())
            throw jbr::reg::exception("The register " + pathOld + " is not movable. Please check the register rights, write, read and copy must be allow.");

        std::error_code     ec;

        std::filesystem::rename(pathOld, pathNew, ec);
        if (ec)
            throw jbr::reg::exception("Impossible to move this next register : " + pathOld + " to : " + pathNew + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message() + '.');
    }

    void    Register::destroy(const std::string &path)
    {
        if (path.empty())
            throw jbr::reg::exception("To destroy a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to destroy a not existing register : " + path + ".");
        verify(path);
        if (!isDestroyable())
            throw jbr::reg::exception("The register " + path + " is not destroyable. Please check the register rights, write, read and destroy must be allow.");

        std::error_code     ec;

        if (!std::filesystem::remove(path, ec))
            throw jbr::reg::exception("Impossible to destroy this next register : " + path + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message() + '.');
    }

    jbr::reg::Rights    Register::rights(const std::string &path)
    {
        if (path.empty())
            throw jbr::reg::exception("To get register rights, the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to extract register rights from a not existing register : " + path + ".");
        verify(path);
        return (mRights);
    }

    void                Register::applyRights(const std::string &path, const jbr::reg::Rights &rights)
    {
        (void)rights;
        if (path.empty())
            throw jbr::reg::exception("To apply new register rights, the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to apply new register rights from a not existing register : " + path + ".");
        verify(path);
        /**
         * Faire l'application des droits ...
         */
    }

    void    Register::createHeader(const std::string &path, const std::optional<jbr::reg::Rights> &rights) const
    {
        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLNode       *nodeReg = reg.NewElement("register");
        tinyxml2::XMLNode       *nodeHeader = reg.NewElement("header");
        tinyxml2::XMLNode       *nodeBody = reg.NewElement("body");
        tinyxml2::XMLElement    *version = reg.NewElement("version");

        if (nodeReg == nullptr || nodeHeader == nullptr || nodeBody == nullptr || version == nullptr)
            throw jbr::reg::exception("Error while saving the register content, null pointer detected.");
        reg.InsertFirstChild(nodeReg);
        nodeReg->InsertFirstChild(nodeHeader);
        nodeReg->InsertAfterChild(nodeHeader, nodeBody);
        version->SetText(1.0);
        nodeHeader->InsertEndChild(version);

        if (rights != std::nullopt)
        {
            tinyxml2::XMLNode       *nodeRights = reg.NewElement("rights");
            tinyxml2::XMLElement    *readElement = reg.NewElement("read");
            tinyxml2::XMLElement    *writeElement = reg.NewElement("write");
            tinyxml2::XMLElement    *openElement = reg.NewElement("open");
            tinyxml2::XMLElement    *copyElement = reg.NewElement("copy");
            tinyxml2::XMLElement    *moveElement = reg.NewElement("move");
            tinyxml2::XMLElement    *destroyElement = reg.NewElement("destroy");

            if (nodeRights == nullptr || readElement == nullptr || writeElement == nullptr || openElement == nullptr ||
                copyElement == nullptr || moveElement == nullptr || destroyElement == nullptr)
                throw jbr::reg::exception("Error while saving the register content, null pointer detected.");
            nodeHeader->InsertAfterChild(version, nodeRights);
            readElement->SetText(rights->mRead);
            writeElement->SetText(rights->mWrite);
            openElement->SetText(rights->mOpen);
            copyElement->SetText(rights->mCopy);
            moveElement->SetText(rights->mMove);
            destroyElement->SetText(rights->mDestroy);
            nodeRights->InsertFirstChild(readElement);
            nodeRights->InsertAfterChild(readElement, writeElement);
            nodeRights->InsertAfterChild(writeElement, openElement);
            nodeRights->InsertAfterChild(openElement, copyElement);
            nodeRights->InsertAfterChild(copyElement, moveElement);
            nodeRights->InsertAfterChild(moveElement, destroyElement);
        }

        tinyxml2::XMLError  err = reg.SaveFile(path.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Error while saving the register content, error code : " + std::to_string(err) + ".");
    }

    void    Register::verifyRights(tinyxml2::XMLNode  *nodeHeader)
    {
        tinyxml2::XMLNode       *nodeRights = nodeHeader->FirstChildElement("rights");
        tinyxml2::XMLError      err;

        if (nodeRights == nullptr)
            return ;

        tinyxml2::XMLElement    *readElement = nodeRights->FirstChildElement("read");
        tinyxml2::XMLElement    *writeElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *openElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *copyElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *moveElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *destroyElement = nodeRights->FirstChildElement("write");

        if (readElement != nullptr)
        {
            err = readElement->QueryBoolText(&mRights.mRead);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field read from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
        if (writeElement != nullptr)
        {
            err = writeElement->QueryBoolText(&mRights.mWrite);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field write from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
        if (openElement != nullptr)
        {
            err = openElement->QueryBoolText(&mRights.mOpen);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field open from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
        if (copyElement != nullptr)
        {
            err = copyElement->QueryBoolText(&mRights.mCopy);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field copy from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
        if (moveElement != nullptr)
        {
            err = moveElement->QueryBoolText(&mRights.mMove);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field move from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
        if (destroyElement != nullptr)
        {
            err = destroyElement->QueryBoolText(&mRights.mDestroy);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field destroy from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
    }

}