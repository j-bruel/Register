//!
//! @file Register.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include "jbr/reg/Manager.hpp"
#include "jbr/reg/exception.hpp"

namespace jbr::reg
{

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

    void    Instance::saveXMLFile(tinyxml2::XMLDocument &xmlDocument) const noexcept(false)
    {
        tinyxml2::XMLError      err = xmlDocument.SaveFile(mPath.c_str());

        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Error while saving the register content, error code : " + std::to_string(err) + ".");
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

}
