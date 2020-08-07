//!
//! @file update_test.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("jbr::reg::Variable::update")
{

    SUBCASE("Update a variable.")
    {
        jbr::reg::Variable  var("key", "value");

        CHECK_NOTHROW(var.update("updated"));
        CHECK(std::string(var.read()) == "updated");
    }

    SUBCASE("Update from empty variable.")
    {
        jbr::reg::Variable  var("key");

        CHECK_NOTHROW(var.update("updated"));
        CHECK(std::string(var.read()) == "updated");
    }

    SUBCASE("Update to empty variable.")
    {
        jbr::reg::Variable  var("key", "value");

        CHECK_NOTHROW(var.update(""));
        CHECK(std::string(var.read()).empty());
    }

    SUBCASE("Update a variable without reading right.")
    {
        jbr::reg::Variable  var("key", "value", jbr::reg::var::perm::Rights(true, true, false, true, true, true));
        std::string         msg;

        try {
            (void)var.update("updated");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(std::string(var.read()) == "value");
        CHECK(msg == "Impossible to update a register variable, the 'write' and 'update' rights must be set to true.");
    }

}
