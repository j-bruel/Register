//!
//! @file read_test.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <cstring>
#include <doctest.h>

TEST_CASE("jbr::reg::Variable::read")
{

    SUBCASE("Read a variable.")
    {
        jbr::reg::Variable  var("key", "value");
        std::string         value(var.read());

        CHECK(value == "value");
    }

    SUBCASE("Read a empty variable.")
    {
        jbr::reg::Variable  var("key");
        std::string         value(var.read());

        CHECK(value.empty());
    }

    SUBCASE("Read a variable without key set.")
    {
        std::string msg;

        try {
            jbr::reg::Variable  var("", "value");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to set a empty register variable.");
    }

    SUBCASE("Read a variable without reading right.")
    {
        jbr::reg::Variable  var("key", "value", jbr::reg::var::perm::Rights(false, true, true, true, true, true));
        std::string         msg;

        try {
            (void)var.read();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to read a register variable, right must be set to true.");
    }

    SUBCASE("Read a copied variable.")
    {
        jbr::reg::Variable  var("key", "value");
        jbr::reg::Variable  var2(var);
        const char          *value = var2.read();

        if (value == nullptr)
            FAIL("The register value should not be null.");
        CHECK_EQ(std::strcmp(value, "value"), 0);
    }

}
