//!
//! @file register_create.cpp
//! @author jbruel
//! @date 20/05/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Manager::create")
{
    SUBCASE("Create register with empty input path.")
    {
        try {
            (void)jbr::reg::Manager::create("");
        }
        catch (jbr::reg::exception &e) {
            CHECK(std::string(e.what()) == "To create a register the path must not be empty.");
            return ;
        }
        FAIL("Create a empty register must throw a exception.");
    }

    SUBCASE("Basic register created.")
    {
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./ut_create_one_register"));
        CHECK(std::filesystem::exists("./ut_create_one_register"));
        std::filesystem::remove("./ut_create_one_register");
    }

    SUBCASE("Create few register on the same frame.")
    {
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./ut_create_1"));
        CHECK_NOTHROW((void)jbr::reg::Manager::create("../ut_create_2"));
        CHECK_NOTHROW((void)jbr::reg::Manager::create("ut_create_3"));
        std::filesystem::create_directory("./nextDirectory");
        CHECK_NOTHROW((void)jbr::reg::Manager::create("./nextDirectory/ut_create_4"));
        CHECK(std::filesystem::exists("./ut_create_1"));
        CHECK(std::filesystem::exists("../ut_create_2"));
        CHECK(std::filesystem::exists("ut_create_3"));
        CHECK(std::filesystem::exists("./nextDirectory/ut_create_4"));
        std::filesystem::remove("./ut_create_1");
        std::filesystem::remove("../ut_create_2");
        std::filesystem::remove("ut_create_3");
        std::filesystem::remove_all("./nextDirectory");
    }

    SUBCASE("Verify the mandatory register content.")
    {
        (void)jbr::reg::Manager::create("ut.reg");

        std::ifstream   ifs("ut.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                        "    <header>\n"
                        "        <version>1.0.0</version>\n"
                        "    </header>\n"
                        "    <body/>\n"
                        "</register>\n");
        ifs.close();
        std::filesystem::remove("ut.reg");
    }

    SUBCASE("Create a register on already existing file.")
    {
        std::string msg;

        CHECK_NOTHROW((void)jbr::reg::Manager::create("./ut_already_1"));
        std::filesystem::create_directory("./ut_already_2");
        try {
            (void)jbr::reg::Manager::create("./ut_already_1");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_already_1 already exist. You must remove it before create it or open it.");
        msg.clear();
        try {
            (void)jbr::reg::Manager::create("./ut_already_2");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./ut_already_2 already exist. You must remove it before create it or open it.");
        std::filesystem::remove_all("./ut_already_1");
        std::filesystem::remove_all("./ut_already_2");
    }

}
