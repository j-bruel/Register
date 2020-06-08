//!
//! @file Variable.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <jbr/reg/var/perm/XMLElement.hpp>
#include <iostream>

namespace jbr::reg
{
    Variable::Variable(const std::string &registerPath) : mPath(registerPath)
    {
        if (mPath.empty())
            throw jbr::reg::exception("Register variable can not be build according a empty register path.");
        if (!exist(mPath))
            throw jbr::reg::exception("Register variable can not be build according a not existing register : " + mPath + '.');
        open(registerPath);
    }

    void        Variable::set(const std::string &key, const std::string &value,
                              const std::optional<jbr::reg::var::perm::Rights> &rights)
    {
        tinyxml2::XMLDocument   reg;

        if (key.empty())
            throw jbr::reg::exception("Impossible to set a empty key.");
        open(mPath);
        reg.LoadFile(mPath.c_str());

        tinyxml2::XMLNode       *nodeReg = getSubXMLNode(&reg, "register");
        tinyxml2::XMLNode       *nodeBody = getSubXMLNode(nodeReg, "body");
        tinyxml2::XMLNode       *nodeVariable = reg.NewElement("variable");

        if (nodeVariable == nullptr)
            throw jbr::reg::exception("Error while setting the register new variable " + key + ", null pointer detected on variable node creation.");
        nodeBody->InsertEndChild(nodeVariable);

        tinyxml2::XMLElement    *keyElementField = reg.NewElement("key");
        tinyxml2::XMLElement    *valueElementField = reg.NewElement("value");

        if (keyElementField == nullptr)
            throw jbr::reg::exception("Error while setting the register new variable " + key + ", impossible to create the key field.");
        if (valueElementField == nullptr)
            throw jbr::reg::exception("Error while setting the register new variable " + key + ", impossible to create the value field.");
        keyElementField->SetText(key.c_str());
        valueElementField->SetText(value.c_str());
        nodeVariable->InsertFirstChild(keyElementField);
        nodeVariable->InsertAfterChild(keyElementField, valueElementField);
        if (rights != std::nullopt)
            writeVariableRights(&reg, nodeVariable, valueElementField, rights.value());

        tinyxml2::XMLError      err;

        err = reg.SaveFile(mPath.c_str());
        if (err != tinyxml2::XMLError::XML_SUCCESS)
            throw jbr::reg::exception("Error while saving the register content, error code : " + std::to_string(err) + ".");
    }

    std::string Variable::get(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to get a empty key.");
        open(mPath);
        /**
         * @todo
         */
        std::cout << "GET:<" << key << ">" << std::endl;
        return ("");
    }

    void        Variable::remove(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to remove a empty key.");
        open(mPath);
        /**
         * @todo
         */
        std::cout << "REMOVE:<" << key << ">>" << std::endl;
    }

    bool        Variable::available(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to check if a empty key exist.");
        open(mPath);
        /**
         * @todo
         */
        std::cout << "EXIST:<" << key << ">" << std::endl;
        return (true);
    }

    tinyxml2::XMLNode   *Variable::getSubXMLNode(tinyxml2::XMLNode *node, const char *subNodeName) noexcept(false)
    {
        if (node == nullptr)
            throw jbr::reg::exception("Error while extracting sub node, the parent node is null.");
        if (subNodeName == nullptr)
            throw jbr::reg::exception("The sub node name to extract is null.");

        tinyxml2::XMLNode   *subNode = node->FirstChildElement(subNodeName);

        if (subNode == nullptr)
            throw jbr::reg::exception("Error while extract the sub node, the result is null. The sub node " + std::string(subNodeName) + " does not exist.");
        return (subNode);
    }

    void    Variable::writeVariableRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeVariable,
                                          tinyxml2::XMLElement *valueElement,
                                          const jbr::reg::var::perm::Rights &rights) noexcept(false)
    {
        if (reg == nullptr || nodeVariable == nullptr)
            throw jbr::reg::exception("Pointers must not be null during writing rights process.");

        tinyxml2::XMLNode       *nodeConfig = reg->NewElement("config");
        tinyxml2::XMLNode       *nodeRights = reg->NewElement("rights");
        var::perm::XMLElement   xmlElements(reg);

        if (nodeConfig == nullptr || nodeRights == nullptr)
            throw jbr::reg::exception("Error while saving the variable rights content, null pointer detected.");
        nodeVariable->InsertAfterChild(valueElement, nodeConfig);
        nodeConfig->InsertFirstChild(nodeRights);
        xmlElements.setText(rights);
        nodeRights->InsertFirstChild(xmlElements.mReadElement);
        nodeRights->InsertAfterChild(xmlElements.mReadElement, xmlElements.mWriteElement);
        nodeRights->InsertAfterChild(xmlElements.mWriteElement, xmlElements.mUpdateElement);
        nodeRights->InsertAfterChild(xmlElements.mUpdateElement, xmlElements.mRenameElement);
        nodeRights->InsertAfterChild(xmlElements.mRenameElement, xmlElements.mCopyElement);
        nodeRights->InsertAfterChild(xmlElements.mCopyElement, xmlElements.mRemoveElement);
    }

}
