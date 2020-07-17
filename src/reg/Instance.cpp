//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/reg/Manager.hpp"
#include "jbr/reg/exception.hpp"

namespace jbr::reg
{

    void    Instance::verify() const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;

        if (!exist())
            throw jbr::reg::exception("Impossible to check the corruption status of a not existing register : " + mPath + '.');
        loadXMLFile(reg);

        tinyxml2::XMLNode       *nodeReg = getSubXMLElement(&reg, "register");
        tinyxml2::XMLNode       *nodeHeader = getSubXMLElement(nodeReg, "header");
        tinyxml2::XMLElement    *version = getSubXMLElement(nodeHeader, "version");
        const char              *versionValue;

        versionValue = version->GetText();
        if (versionValue == nullptr)
            throw jbr::reg::exception("Register corrupted. Field version from register/header nodes not set or invalid.");
        verifyRights(nodeHeader);
        (void)getSubXMLElement(nodeReg, "body");
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
        tinyxml2::XMLError      err = xmlDocument.LoadFile(mPath.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Parsing error while loading the register file, error code : " + std::to_string(err) + '.');
    }

    void    Instance::createHeader(const std::optional<jbr::reg::Rights> &rights) const noexcept(false)
    {
        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLNode       *nodeReg = newXMLElement(&reg, "register");
        tinyxml2::XMLNode       *nodeHeader = newXMLElement(&reg, "header");
        tinyxml2::XMLNode       *nodeBody = newXMLElement(&reg, "body");
        tinyxml2::XMLElement    *version = newXMLElement(&reg, "version");

        reg.InsertFirstChild(nodeReg);
        nodeReg->InsertFirstChild(nodeHeader);
        nodeReg->InsertAfterChild(nodeHeader, nodeBody);
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
        tinyxml2::XMLElement    *readElement = newXMLElement(reg, "read");
        tinyxml2::XMLElement    *writeElement = newXMLElement(reg, "write");
        tinyxml2::XMLElement    *openElement = newXMLElement(reg, "open");
        tinyxml2::XMLElement    *copyElement = newXMLElement(reg, "copy");
        tinyxml2::XMLElement    *moveElement = newXMLElement(reg, "move");
        tinyxml2::XMLElement    *destroyElement = newXMLElement(reg, "destroy");

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

    void    Instance::verifyRights(tinyxml2::XMLNode *nodeHeader) const noexcept(false)
    {
        tinyxml2::XMLNode   *nodeRights = nodeHeader->FirstChildElement("rights");

        if (nodeRights == nullptr)
            return ;

        tinyxml2::XMLElement    *readElement = nodeRights->FirstChildElement("read");
        tinyxml2::XMLElement    *writeElement = nodeRights->FirstChildElement("write");
        tinyxml2::XMLElement    *openElement = nodeRights->FirstChildElement("open");
        tinyxml2::XMLElement    *copyElement = nodeRights->FirstChildElement("copy");
        tinyxml2::XMLElement    *moveElement = nodeRights->FirstChildElement("move");
        tinyxml2::XMLElement    *destroyElement = nodeRights->FirstChildElement("destroy");
        jbr::reg::Rights        rights;

        queryRightToXMLElement(readElement, &rights.mRead);
        queryRightToXMLElement(writeElement, &rights.mWrite);
        queryRightToXMLElement(openElement, &rights.mOpen);
        queryRightToXMLElement(copyElement, &rights.mCopy);
        queryRightToXMLElement(moveElement, &rights.mMove);
        queryRightToXMLElement(destroyElement, &rights.mDestroy);
    }

    void    Instance::queryRightToXMLElement(tinyxml2::XMLElement *xmlElement, bool *status) const noexcept(false)
    {
        tinyxml2::XMLError      err;

        if (xmlElement != nullptr)
        {
            err = xmlElement->QueryBoolText(status);
            if (err != tinyxml2::XMLError::XML_SUCCESS)
                throw jbr::reg::exception("Register corrupted. Field " + std::string(xmlElement->Name()) + " from register/header/rights nodes is invalid, error code : " + std::to_string(err) + '.');
        }
    }

}
