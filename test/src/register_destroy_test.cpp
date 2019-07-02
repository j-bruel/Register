//!
//! @file register_destroy.cpp
//! @author jbruel
//! @date 05/06/19
//!

/*
#include <doctest.h>
#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <filesystem>
#include <iostream>
*/
#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("Register::destroy")
{
//    jbr::Register   mRegister;
/*
 *
    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.destroy("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To destroy a register the path must not be empty.");
    }

    SUBCASE("destroy one")
    {
        mRegister.create("./ut_destroy_one_register");
        CHECK_NOTHROW(mRegister.destroy("./ut_destroy_one_register"));
        CHECK(!std::filesystem::exists("./ut_destroy_one_register"));
    }

    SUBCASE("destroy few")
    {
        mRegister.create("./ut_destroy_1");
        mRegister.create("../ut_destroy_2");
        mRegister.create("ut_destroy_3");
        std::filesystem::create_directory("./nextDirectory");
        mRegister.create("./nextDirectory/ut_destroy_4");
        CHECK_NOTHROW(mRegister.destroy("./ut_destroy_1"));
        CHECK_NOTHROW(mRegister.destroy("../ut_destroy_2"));
        CHECK_NOTHROW(mRegister.destroy("ut_destroy_3"));
        CHECK_NOTHROW(mRegister.destroy("./nextDirectory/ut_destroy_4"));
        CHECK(!std::filesystem::exists("./ut_create_1"));
        CHECK(!std::filesystem::exists("../ut_create_2"));
        CHECK(!std::filesystem::exists("ut_create_3"));
        CHECK(!std::filesystem::exists("./nextDirectory/ut_create_4"));
        std::filesystem::remove("./ut_destroy_1");
        std::filesystem::remove("../ut_destroy_2");
        std::filesystem::remove("ut_destroy_3");
        std::filesystem::remove_all("./nextDirectory");
    }

    SUBCASE("not exist")
    {
        std::string msg;

        try {
            mRegister.destroy("./ut_not_exist");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to destroy a not existing register : ./ut_not_exist.");
    }*/

}
