//!
//! @file destroy_test.cpp
//! @author jbruel
//! @date 22/07/20
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Manager::destroy")
{

    SUBCASE("Destroy a basic register.")
    {
        jbr::Register reg = jbr::reg::Manager::create("./ut_destroy_one_register.reg");

        CHECK_NOTHROW(jbr::reg::Manager::destroy(reg));
        CHECK(!std::filesystem::exists("./ut_destroy_one_register.reg"));
    }

    SUBCASE("Destroy few registers in multiple locations.")
    {
        std::filesystem::create_directory("./nextDirectory");

        jbr::Register destroy1 = jbr::reg::Manager::create("./ut_destroy_1.reg");
        jbr::Register destroy2 = jbr::reg::Manager::create("../ut_destroy_2.reg");
        jbr::Register destroy3 = jbr::reg::Manager::create("ut_destroy_3.reg");
        jbr::Register destroy4 = jbr::reg::Manager::create("./nextDirectory/ut_destroy_4.reg");

        CHECK_NOTHROW(jbr::reg::Manager::destroy(destroy1));
        CHECK_NOTHROW(jbr::reg::Manager::destroy(destroy2));
        CHECK_NOTHROW(jbr::reg::Manager::destroy(destroy3));
        CHECK_NOTHROW(jbr::reg::Manager::destroy(destroy4));
        CHECK(!std::filesystem::exists("./ut_create_1.reg"));
        CHECK(!std::filesystem::exists("../ut_create_2.reg"));
        CHECK(!std::filesystem::exists("ut_create_3.reg"));
        CHECK(!std::filesystem::exists("./nextDirectory/ut_create_4.reg"));
        std::filesystem::remove("./ut_destroy_1.reg");
        std::filesystem::remove("../ut_destroy_2.reg");
        std::filesystem::remove("ut_destroy_3.reg");
        std::filesystem::remove_all("./nextDirectory");
    }

    SUBCASE("Destroy a not existing register.")
    {
        std::string msg;
        jbr::Register destroy = jbr::reg::Manager::create("./destroy_not_existing.reg");

        std::filesystem::remove("./destroy_not_existing.reg");
        try {
            jbr::reg::Manager::destroy(destroy);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./destroy_not_existing.reg.");
    }

    SUBCASE("Try to destroy a register without destroy rights.")
    {
        jbr::Register   destroy = jbr::reg::Manager::create("./destroy_without_destroy_right.reg",
                                                            jbr::reg::Rights(true, true, true, true, true, false));
        std::string     msg;

        try {
            jbr::reg::Manager::destroy(destroy);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./destroy_without_destroy_right.reg is not destroyable. Please check the register rights, read and destroy must be allow.");
        CHECK(jbr::reg::Manager::exist("./destroy_without_destroy_right.reg"));
        std::filesystem::remove("./destroy_without_destroy_right.reg");
    }

    SUBCASE("Try to destroy two time the same register.")
    {
        jbr::Register   destroy = jbr::reg::Manager::create("./destroy_two_time.reg");
        std::string     msg;

        CHECK_NOTHROW(jbr::reg::Manager::destroy(destroy));
        try {
            jbr::reg::Manager::destroy(destroy);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./destroy_two_time.reg.");
        std::filesystem::remove("./destroy_two_time.reg");
    }

    SUBCASE("Try to destroy a register without read rights.")
    {
        jbr::Register   destroy = jbr::reg::Manager::create("./destroy_without_read_right.reg",
                                                            jbr::reg::Rights(false, true, true, true, true, true));
        std::string     msg;

        try {
            jbr::reg::Manager::destroy(destroy);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./destroy_without_read_right.reg is not destroyable. Please check the register rights, read and destroy must be allow.");
        CHECK(jbr::reg::Manager::exist("./destroy_without_read_right.reg"));
        std::filesystem::remove("./destroy_without_read_right.reg");
    }

}
