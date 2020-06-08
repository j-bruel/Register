//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/Register.hpp"
#include "jbr/reg/Variable.hpp"
#include "jbr/reg/exception.hpp"
#include <iostream>
#include <filesystem>

namespace jbr
{

    jbr::reg::Variable  Register::operator[](const std::string &path) { return (jbr::reg::Variable(path)); }

    void    Register::create(const std::string &path, const std::optional<jbr::reg::Rights> &rights) const noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To create a register the path must not be empty.");
        if (exist(path))
            throw jbr::reg::exception("The register " + path + " already exist. You must remove it before create it or open it.");
        createHeader(path, rights);
    }

    void    Register::open(const std::string &path) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To open a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("The register " + path + " does not exist. You must create it before.");
        verify(path);
        if (!isOpenable())
            throw jbr::reg::exception("The register " + path + " is not openable. Please check the register rights, read and open must be allowed.");
    }

    bool    Register::exist(const std::string &path) noexcept
    {
        if (path.empty())
            return (false);

        std::error_code     ec;

        return (std::filesystem::exists(path, ec));
    }

    void    Register::verify(const std::string &path) noexcept(false)
    {
        tinyxml2::XMLDocument   reg;

        if (path.empty())
            throw jbr::reg::exception("To check if a register is corrupt the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to check the corruption status of a not existing register : " + path + '.');
        loadXMLFile(reg, path.c_str());

        tinyxml2::XMLNode       *nodeReg = getSubXMLElement(&reg, "register");
        tinyxml2::XMLNode       *nodeHeader = getSubXMLElement(nodeReg, "header");
        tinyxml2::XMLElement    *version = getSubXMLElement(nodeHeader, "version");
        tinyxml2::XMLError      err;
        double                  versionValue;

        err = version->QueryDoubleText(&versionValue);
        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Register corrupted. Field version from register/header nodes not set or invalid, error code : " + std::to_string(err) + '.');
        verifyRights(nodeHeader);
        getSubXMLElement(nodeReg, "body");
    }

    void    Register::copy(const std::string &pathFrom, const std::string &pathTo) noexcept(false)
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

    void    Register::move(const std::string &pathOld, const std::string &pathNew)noexcept(false)
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

    void    Register::destroy(const std::string &path) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To destroy a register the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to destroy a not existing register : " + path + ".");
        verify(path);
        if (!isDestroyable())
            throw jbr::reg::exception("The register " + path + " is not destroyable. Please check the register rights, read and destroy must be allow.");

        std::error_code     ec;

        if (!std::filesystem::remove(path, ec))
            throw jbr::reg::exception("Impossible to destroy this next register : " + path + ". Error code : " + std::to_string(ec.value()) + ", why : " + ec.message() + '.');
    }

    jbr::reg::Rights    Register::rights(const std::string &path) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To get register rights, the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to extract register rights from a not existing register : " + path + ".");
        verify(path);
        if (!mRights.mRead)
            throw jbr::reg::exception("The register " + path + " is not readable. Please check the register rights, read must be allow.");
        return (mRights);
    }

    void                Register::applyRights(const std::string &path, const jbr::reg::Rights &rights) noexcept(false)
    {
        if (path.empty())
            throw jbr::reg::exception("To apply new register rights, the path must not be empty.");
        if (!exist(path))
            throw jbr::reg::exception("Impossible to apply new register rights from a not existing register : " + path + ".");
        verify(path);
        if (!mRights.mWrite)
            throw jbr::reg::exception("The register " + path + " is not writable. Please check the register rights, write must be allow.");

        tinyxml2::XMLDocument   reg;

        loadXMLFile(reg, path.c_str());

        tinyxml2::XMLNode       *nodeReg = getSubXMLElement(&reg, "register");
        tinyxml2::XMLNode       *nodeHeader = getSubXMLElement(nodeReg, "header");
        tinyxml2::XMLElement    *version = getSubXMLElement(nodeHeader, "version");

        writeRights(&reg, nodeHeader, version, rights);
        saveXMLFile(reg, path.c_str());
    }

    void    Register::createHeader(const std::string &path, const std::optional<jbr::reg::Rights> &rights) const noexcept(false)
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
            writeRights(&reg, nodeHeader, version, rights.value());
        saveXMLFile(reg, path.c_str());
    }

    void    Register::verifyRights(tinyxml2::XMLNode  *nodeHeader) noexcept(false)
    {
        tinyxml2::XMLNode       *nodeRights = nodeHeader->FirstChildElement("rights");
        tinyxml2::XMLError      err;

        if (nodeRights == nullptr)
            return ;

        tinyxml2::XMLElement    *readElement = nodeRights->FirstChildElement("read");
        tinyxml2::XMLElement    *writeElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *openElement = nodeRights->FirstChildElement("open");
        tinyxml2::XMLElement    *copyElement = nodeRights->FirstChildElement("copy");
        tinyxml2::XMLElement    *moveElement = nodeRights->FirstChildElement("move");
        tinyxml2::XMLElement    *destroyElement = nodeRights->FirstChildElement("destroy");

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

    void    Register::writeRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeHeader,
                                  tinyxml2::XMLElement *version, const jbr::reg::Rights &rights) const noexcept(false)
    {
        if (reg == nullptr || nodeHeader == nullptr || version == nullptr)
            throw jbr::reg::exception("Pointers must not be null during writing rights process.");

        tinyxml2::XMLNode       *nodeRights = reg->NewElement("rights");
        tinyxml2::XMLElement    *readElement = reg->NewElement("read");
        tinyxml2::XMLElement    *writeElement = reg->NewElement("write");
        tinyxml2::XMLElement    *openElement = reg->NewElement("open");
        tinyxml2::XMLElement    *copyElement = reg->NewElement("copy");
        tinyxml2::XMLElement    *moveElement = reg->NewElement("move");
        tinyxml2::XMLElement    *destroyElement = reg->NewElement("destroy");

        if (nodeRights == nullptr || readElement == nullptr || writeElement == nullptr || openElement == nullptr ||
            copyElement == nullptr || moveElement == nullptr || destroyElement == nullptr)
            throw jbr::reg::exception("Error while saving the register content, null pointer detected.");
        nodeHeader->InsertAfterChild(version, nodeRights);
        readElement->SetText(rights.mRead);
        writeElement->SetText(rights.mWrite);
        openElement->SetText(rights.mOpen);
        copyElement->SetText(rights.mCopy);
        moveElement->SetText(rights.mMove);
        destroyElement->SetText(rights.mDestroy);
        nodeRights->InsertFirstChild(readElement);
        nodeRights->InsertAfterChild(readElement, writeElement);
        nodeRights->InsertAfterChild(writeElement, openElement);
        nodeRights->InsertAfterChild(openElement, copyElement);
        nodeRights->InsertAfterChild(copyElement, moveElement);
        nodeRights->InsertAfterChild(moveElement, destroyElement);
    }

    tinyxml2::XMLElement    *Register::getSubXMLElement(tinyxml2::XMLNode *node, const char *subNodeName) noexcept(false)
    {
        if (node == nullptr)
            throw jbr::reg::exception("Error while extracting sub node, the parent node is null.");
        if (subNodeName == nullptr)
            throw jbr::reg::exception("The sub node name to extract is null.");

        tinyxml2::XMLElement    *subNode = node->FirstChildElement(subNodeName);

        if (subNode == nullptr)
            throw jbr::reg::exception("Error while extract the sub node, the result is null. The sub node " + std::string(subNodeName) + " does not exist.");
        return (subNode);
    }

    tinyxml2::XMLElement    *Register::newXMLElement(tinyxml2::XMLDocument *xmlDocument, const char *elementName) noexcept(false)
    {
        if (xmlDocument == nullptr)
            throw jbr::reg::exception("Error while creating a new element, the parent document is null.");
        if (elementName == nullptr)
            throw jbr::reg::exception("The new element name to create is null.");

        tinyxml2::XMLElement   *newElement = xmlDocument->NewElement(elementName);

        if (newElement == nullptr)
            throw jbr::reg::exception("Error while creating a new element, the result is null. The element " + std::string(elementName) + " can't be created.");
        return (newElement);
    }

    void    Register::loadXMLFile(tinyxml2::XMLDocument &xmlDocument, const char *filePath) noexcept(false)
    {
        if (filePath == nullptr)
            throw jbr::reg::exception("The register path to load is null.");

        tinyxml2::XMLError      err = xmlDocument.LoadFile(filePath);

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Parsing error while loading the register file, error code : " + std::to_string(err) + '.');
    }

    void    Register::saveXMLFile(tinyxml2::XMLDocument &xmlDocument, const char *filePath) noexcept(false)
    {
        if (filePath == nullptr)
            throw jbr::reg::exception("The register path to save is null.");

        tinyxml2::XMLError      err = xmlDocument.SaveFile(filePath);

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Error while saving the register content, error code : " + std::to_string(err) + ".");
    }

}
