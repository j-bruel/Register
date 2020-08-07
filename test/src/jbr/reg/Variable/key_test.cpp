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

    SUBCASE("Get key of a variable.")
    {
        jbr::reg::Variable  var("key", "value");
        const char          *key = var.key();

        if (key == nullptr)
            FAIL("The register should not be null.");
        CHECK_EQ(std::strcmp(key, "key"), 0);
    }

    SUBCASE("Read a variable without reading right.")
    {
        jbr::reg::Variable  var("key", "value", jbr::reg::var::perm::Rights(false, true, true, true, true, true));
        std::string         msg;

        try {
            (void)var.key();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to read a register variable, right must be set to true.");
    }

}
