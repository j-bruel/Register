//!
//! @file Variable.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include "jbr/reg/Variable.hpp"
#include "jbr/reg/exception.hpp"
#include <iostream>
#include <tinyxml2.h>


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

    void        Variable::set(const std::string &key, const std::string &value, const std::optional<jbr::reg::var::Rights> &rights)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to set a empty key.");
        open(mPath);

        tinyxml2::XMLDocument   reg;
        tinyxml2::XMLError      err;

        reg.LoadFile(mPath.c_str());

        tinyxml2::XMLNode       *nodeReg = reg.FirstChildElement("register");

        if (nodeReg == nullptr)
            throw jbr::reg::exception("Error while setting the register new variable " + key + ", register node not found.");

        tinyxml2::XMLNode       *nodeBody = nodeReg->FirstChildElement("body");
        tinyxml2::XMLNode       *nodeVariable = reg.NewElement("variable");

        if (nodeBody == nullptr)
            throw jbr::reg::exception("Error while setting the register new variable " + key + ", register/body node not found.");
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

    void    Variable::writeVariableRights(tinyxml2::XMLDocument *reg, tinyxml2::XMLNode *nodeVariable,
            tinyxml2::XMLElement *valueElement, const jbr::reg::var::Rights &rights) const
    {
        if (reg == nullptr || nodeVariable == nullptr)
            throw jbr::reg::exception("Pointers must not be null during writing rights process.");

        tinyxml2::XMLNode       *nodeConfig = reg->NewElement("config");
        tinyxml2::XMLNode       *nodeRights = reg->NewElement("rights");
        tinyxml2::XMLElement    *readElement = reg->NewElement("read");
        tinyxml2::XMLElement    *writeElement = reg->NewElement("write");
        tinyxml2::XMLElement    *updateElement = reg->NewElement("update");
        tinyxml2::XMLElement    *renameElement = reg->NewElement("rename");
        tinyxml2::XMLElement    *copyElement = reg->NewElement("copy");
        tinyxml2::XMLElement    *removeElement = reg->NewElement("remove");

        if (nodeConfig == nullptr || nodeRights == nullptr || readElement == nullptr || writeElement == nullptr ||
            updateElement == nullptr || renameElement == nullptr || copyElement == nullptr || removeElement == nullptr)
            throw jbr::reg::exception("Error while saving the variable rights content, null pointer detected.");
        nodeVariable->InsertAfterChild(valueElement, nodeConfig);
        nodeConfig->InsertFirstChild(nodeRights);
        readElement->SetText(rights.mRead);
        writeElement->SetText(rights.mWrite);
        updateElement->SetText(rights.mUpdate);
        renameElement->SetText(rights.mCopy);
        copyElement->SetText(rights.mCopy);
        removeElement->SetText(rights.mRemove);
        nodeRights->InsertFirstChild(readElement);
        nodeRights->InsertAfterChild(readElement, writeElement);
        nodeRights->InsertAfterChild(writeElement, updateElement);
        nodeRights->InsertAfterChild(updateElement, renameElement);
        nodeRights->InsertAfterChild(renameElement, copyElement);
        nodeRights->InsertAfterChild(copyElement, removeElement);
    }

}
