//!
//! @file register_create.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>

TEST_CASE("Register::create")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.create("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To create a register the path must not be empty.");
    }

    SUBCASE("create one")
    {
        CHECK_NOTHROW(mRegister.create("./ut_create_one_register"));
        CHECK(std::filesystem::exists("./ut_create_one_register"));
        std::filesystem::remove("./ut_create_one_register");
    }

    SUBCASE("create few")
    {
        CHECK_NOTHROW(mRegister.create("./ut_create_1"));
        CHECK_NOTHROW(mRegister.create("../ut_create_2"));
        CHECK_NOTHROW(mRegister.create("ut_create_3"));
        std::filesystem::create_directory("./nextDirectory");
        CHECK_NOTHROW(mRegister.create("./nextDirectory/ut_create_4"));
        CHECK(std::filesystem::exists("./ut_create_1"));
        CHECK(std::filesystem::exists("../ut_create_2"));
        CHECK(std::filesystem::exists("ut_create_3"));
        CHECK(std::filesystem::exists("./nextDirectory/ut_create_4"));
        std::filesystem::remove("./ut_create_1");
        std::filesystem::remove("../ut_create_2");
        std::filesystem::remove("ut_create_3");
        std::filesystem::remove_all("./nextDirectory");
    }

    SUBCASE("already exist")
    {
        std::string msg;

        CHECK_NOTHROW(mRegister.create("./ut_already_1"));
        std::filesystem::create_directory("./ut_already_2");
        try {
            mRegister.create("./ut_already_1");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_already_1 already exist. You must remove it before create it or open it.");
        msg.clear();
        try {
            mRegister.create("./ut_already_2");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_already_2 already exist. You must remove it before create it or open it.");
        std::filesystem::remove_all("./ut_already_1");
        std::filesystem::remove_all("./ut_already_2");
    }

}
