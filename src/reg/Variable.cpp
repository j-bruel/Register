//!
//! @file Variable.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include "jbr/reg/Variable.hpp"
#include "jbr/Register.hpp"
#include "jbr/reg/exception.hpp"
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

/*    void    Variable::operator=(const std::string &value) const
    {
    }*/

    void        Variable::set(const std::string &key, const std::string &value)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to set a empty key.");
        open(mPath);
        std::cout << "SET:<" << key << "><" << value << ">" << std::endl;
    }

    std::string Variable::get(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to get a empty key.");
        open(mPath);
        std::cout << "GET:<" << key << ">" << std::endl;
        return ("");
    }

    void        Variable::remove(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to remove a empty key.");
        open(mPath);
        std::cout << "REMOVE:<" << key << ">>" << std::endl;
    }

    bool        Variable::available(const std::string &key)
    {
        if (key.empty())
            throw jbr::reg::exception("Impossible to check if a empty key exist.");
        open(mPath);
        std::cout << "EXIST:<" << key << ">" << std::endl;
        return (true);
    }

}