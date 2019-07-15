//!
//! @file variable_test.cpp
//! @author jbruel
//! @date 15/07/19
//!

#include <doctest.h>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>

TEST_CASE("Register::applyRights")
{

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            jbr::reg::Variable variable("");
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
            jbr::reg::Variable variable("./variable_not_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register variable can not be build according a not existing register : ./variable_not_exist.reg.");
    }

    SUBCASE("valid register")
    {
        jbr::Register   reg;

        reg.create("./valid.reg");

        jbr::reg::Variable variable("./valid.reg");

        reg.destroy("./valid.reg");
    }

}