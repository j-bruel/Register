//!
//! @file variable_test.cpp
//! @author jbruel
//! @date 15/07/19
//!

#include <doctest.h>
#include <jbr/Register.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>

TEST_CASE("Variable::operator")
{

    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            (void)mRegister[""].get("none");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register variable can not be build according a empty register path.");
    }

    SUBCASE("not existing register")
    {
        std::string msg;

        try {
            (void)mRegister["./not_exist.reg"].get("none");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register variable can not be build according a not existing register : ./not_exist.reg.");
    }

    SUBCASE("valid register")
    {
        mRegister.create("./valid.reg");
        (void)mRegister["./valid.reg"].get("none");
        mRegister.destroy("./valid.reg");
    }

}
