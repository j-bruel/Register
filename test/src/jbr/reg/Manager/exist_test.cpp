//!
//! @file create_test.cpp
//! @author jbruel
//! @date 22/07/20
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Manager::exist")
{
    SUBCASE("Give empty input path.")
    {
        CHECK(!jbr::reg::Manager::exist(""));
    }

    SUBCASE("Basic register exist check.")
    {
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./exist.reg"));
        CHECK(jbr::reg::Manager::exist("./exist.reg"));
        std::filesystem::remove("./exist.reg");
    }

    SUBCASE("Register not existing.")
    {
        CHECK(!jbr::reg::Manager::exist("./not_exist.reg"));
        CHECK(!jbr::reg::Manager::exist("./not_exist.reg")); // And check if exist does not create this register.
    }

}
