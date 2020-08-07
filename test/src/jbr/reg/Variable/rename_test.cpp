//!
//! @file rename_test.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("jbr::reg::Variable::rename")
{

    SUBCASE("Rename a variable.")
    {
        jbr::reg::Variable  var("key", "value");

        CHECK_NOTHROW(var.rename("updated"));
        CHECK(std::string(var.key()) == "updated");
    }

    SUBCASE("Rename with a empty variable name.")
    {
        jbr::reg::Variable  var("key");
        std::string         msg;

        try {
            var.rename("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to rename a register variable to a empty value.");
        CHECK(std::string(var.key()) == "key");
    }

    SUBCASE("Update a variable without rename right.")
    {
        jbr::reg::Variable  var("key", "value", jbr::reg::var::perm::Rights(true, true, true, false, true, true));
        std::string         msg;

        try {
            var.rename("updated");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(std::string(var.read()) == "value");
        CHECK(msg == "Impossible to rename a register variable, the 'read', 'update' and 'rename' rights must be set to true.");
    }

}
