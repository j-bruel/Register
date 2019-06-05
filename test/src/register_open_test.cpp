//!
//! @file register_open.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <doctest.h>
#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <iostream>
#include <string>
#include <fstream>

TEST_CASE("Register::open")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.open("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To open a register the path must not be empty.");
    }

    SUBCASE("open one")
    {
        std::ofstream("./ut_open_one_register");
        CHECK_NOTHROW(mRegister.open("./ut_open_one_register"));
        std::filesystem::remove("./ut_open_one_register");
    }

    SUBCASE("open few")
    {
        CHECK_NOTHROW(mRegister.create("./ut_open_1"));
        CHECK_NOTHROW(mRegister.create("../ut_open_2"));
        CHECK_NOTHROW(mRegister.create("ut_open_3"));
        std::filesystem::create_directory("./nextDirectory");
        CHECK_NOTHROW(mRegister.create("./nextDirectory/ut_open_4"));
        std::ofstream("./ut_open_5");
        CHECK_NOTHROW(mRegister.open("./ut_open_1"));
        CHECK_NOTHROW(mRegister.open("../ut_open_2"));
        CHECK_NOTHROW(mRegister.open("ut_open_3"));
        CHECK_NOTHROW(mRegister.open("./nextDirectory/ut_open_4"));
        CHECK_NOTHROW(mRegister.open("./ut_open_5"));
        std::filesystem::remove("./ut_open_1");
        std::filesystem::remove("../ut_open_2");
        std::filesystem::remove("ut_open_3");
        std::filesystem::remove_all("./nextDirectory");
        std::filesystem::remove("./ut_open_5");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.open("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_not_exist does not exist. You must create it before.");
    }

}
