//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/reg/Manager.hpp"
#include "jbr/reg/exception.hpp"
#include "jbr/reg/node/Name.hpp"

namespace jbr::reg
{

    Instance::Instance(const char *path)
    {
        if (path == nullptr)
            throw jbr::reg::exception("The register path is null. It must not be null or empty.");
        mPath = path;
        checkPathValidity();
    }

    void    Instance::verify() const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;

        loadXMLFile(reg);
        verify(reg);
    }

    void    Instance::verify(tinyxml2::XMLDocument &xmlDocument) const noexcept(false)
    {
        tinyxml2::XMLNode       *nodeReg = getSubXMLElement(&xmlDocument, jbr::reg::node::name::reg);
        tinyxml2::XMLElement    *version = getSubXMLElement(getSubXMLElement(nodeReg, jbr::reg::node::name::header),
                                                            jbr::reg::node::name::_header::version);

        if (version->GetText() == nullptr)
            throw jbr::reg::exception("Register corrupted. Field version from register/header nodes not set or invalid.");
        (void)getSubXMLElement(nodeReg, jbr::reg::node::name::body);
    }

    void    Instance::copy(const char *pathTo) const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;
        std::error_code         err;

        if (pathTo == nullptr || !pathTo[0])
            throw jbr::reg::exception("To copy a register the new register path must not be empty.");
        if (jbr::reg::Manager::exist(pathTo))
            throw jbr::reg::exception("Impossible to copy the register " + mPath + ". Target path already have a register existing : " + pathTo + ".");
        loadXMLFile(reg);
        verify(reg);
        if (!isCopyable(reg))
            throw jbr::reg::exception("Impossible to copy the register '" + mPath + "' without copy and read right.");
        std::filesystem::copy_file(mPath, pathTo, err);
        if (err)
            throw jbr::reg::exception(err.message());
    }

    void    Instance::move(const char *pathTo) noexcept(false)
    {
        tinyxml2::XMLDocument   reg;
        std::error_code         err;

        if (pathTo == nullptr || !pathTo[0])
            throw jbr::reg::exception("To move a register the new register path must not be empty.");
        if (jbr::reg::Manager::exist(pathTo))
            throw jbr::reg::exception("Impossible to move the register " + mPath + ". Target path already have a register existing : " + pathTo + ".");
        loadXMLFile(reg);
        verify(reg);
        if (!isMovable(reg))
            throw jbr::reg::exception("Impossible to move the register '" + mPath + "' without move and read right.");
        std::filesystem::rename(mPath, pathTo, err);
        if (err)
            throw jbr::reg::exception(err.message());
        mPath = pathTo;
    }

    jbr::reg::Rights    Instance::rights() const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;

        loadXMLFile(reg);
        return (rights(reg));
    }

    jbr::reg::Rights    Instance::rights(tinyxml2::XMLDocument &xmlDocument) const noexcept(false)
    {
        verify(xmlDocument);

        tinyxml2::XMLNode   *nodeRights = getSubXMLElement(getSubXMLElement(&xmlDocument, jbr::reg::node::name::reg),
                                                           jbr::reg::node::name::header)->FirstChildElement("rights");
        jbr::reg::Rights    rights;

        if (nodeRights == nullptr)
            return (rights);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::read), &rights.mRead);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::write), &rights.mWrite);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::open), &rights.mOpen);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::copy), &rights.mCopy);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::move), &rights.mMove);
        queryRightToXMLElement(nodeRights->FirstChildElement(jbr::reg::node::name::_header::_rights::destroy), &rights.mDestroy);
        return (rights);
    }

    void    Instance::applyRights(const jbr::reg::Rights &rights) const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;

        loadXMLFile(reg);
        verify(reg);
        if (!isWritable(reg))
            throw jbr::reg::exception("The register " + mPath + " is not writable. Please check the register rights, write must be allow.");

        tinyxml2::XMLNode       *nodeHeader = getSubXMLElement(getSubXMLElement(&reg, jbr::reg::node::name::reg),
                                                                jbr::reg::node::name::header);

        writeRights(&reg, nodeHeader, getSubXMLElement(nodeHeader, jbr::reg::node::name::_header::version), rights);
        saveXMLFile(reg);
    }

    void    Instance::checkPathValidity() const noexcept(false)
    {
        if (mPath.empty())
            throw jbr::reg::exception("The register path is invalid. It must not be empty.");
    }

    tinyxml2::XMLElement    *Instance::newXMLElement(tinyxml2::XMLDocument *xmlDocument, const char *elementName) const noexcept(false)
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

    tinyxml2::XMLElement    *Instance::getSubXMLElement(tinyxml2::XMLNode *node, const char *subNodeName) const noexcept(false)
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

    void    Instance::saveXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false)
    {
        tinyxml2::XMLError      err = xmlDocument.SaveFile(mPath.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Error while saving the register content, error code : " + std::to_string(err) + ".");
    }

    void    Instance::loadXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false)
    {
        if (!exist())
            throw jbr::reg::exception("Impossible to load a not existing xml file : " + mPath + '.');

        tinyxml2::XMLError      err = xmlDocument.LoadFile(mPath.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Parsing error while loading the register file, error code : " + std::to_string(err) + '.');
    }

    void    Instance::createHeader(const std::optional<jbr::reg::Rights> &rights) const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLNode       *nodeReg = newXMLElement(&reg, jbr::reg::node::name::reg);
        tinyxml2::XMLNode       *nodeHeader = newXMLElement(&reg, jbr::reg::node::name::header);
        tinyxml2::XMLElement    *version = newXMLElement(&reg, jbr::reg::node::name::_header::version);

        reg.InsertFirstChild(nodeReg);
        nodeReg->InsertFirstChild(nodeHeader);
        nodeReg->InsertAfterChild(nodeHeader, newXMLElement(&reg, jbr::reg::node::name::body));
        version->SetText("1.0.0");
        nodeHeader->InsertEndChild(version);
        if (rights != std::nullopt)
            writeRights(&reg, nodeHeader, version, rights.value());
        saveXMLFile(reg);
    }

    void    Instance::writeRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeHeader,
                                  tinyxml2::XMLElement *version, const jbr::reg::Rights &rights) const noexcept(false)
    {
        if (reg == nullptr || nodeHeader == nullptr || version == nullptr)
            throw jbr::reg::exception("Pointers must not be null during writing rights process.");

        tinyxml2::XMLNode       *nodeRights = newXMLElement(reg, "rights");
        tinyxml2::XMLElement    *readElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::read);
        tinyxml2::XMLElement    *writeElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::write);
        tinyxml2::XMLElement    *openElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::open);
        tinyxml2::XMLElement    *copyElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::copy);
        tinyxml2::XMLElement    *moveElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::move);
        tinyxml2::XMLElement    *destroyElement = newXMLElement(reg, jbr::reg::node::name::_header::_rights::destroy);

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

    void    Instance::queryRightToXMLElement(const tinyxml2::XMLElement *xmlElement, bool *status) const noexcept(false)
    {
        tinyxml2::XMLError      err;

        if (xmlElement != nullptr)
        {
            err = xmlElement->QueryBoolText(status);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field " + std::string(xmlElement->Name()) +
                                            " from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
    }

}
