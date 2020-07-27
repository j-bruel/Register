//!
//! @file copy_test.cpp
//! @author jbruel
//! @date 27/07/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::copy")
{
    SUBCASE("Empty input path.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./empty_path.reg");
        std::string     msg;

        try {
            reg->copy("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To copy a register the new register path must not be empty.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("NULL input path.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./null_path.reg");
        std::string     msg;

        try {
            reg->copy(nullptr);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To copy a register the new register path must not be empty.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic copy register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_copy.reg");

        CHECK_NOTHROW(reg->copy("./new_basic_copy.reg"));
        CHECK(jbr::reg::Manager::exist("./basic_copy.reg"));
        CHECK(jbr::reg::Manager::exist("./new_basic_copy.reg"));
        jbr::reg::Manager::destroy(reg);
        std::filesystem::remove("./new_basic_copy.reg");
    }

    SUBCASE("Copy a not existing register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./not_existing.reg");
        std::string     msg;

        std::filesystem::remove("./not_existing.reg");
        try {
            reg->copy("./will_not_be_created.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./not_existing.reg.");
        CHECK_FALSE(jbr::reg::Manager::exist("./not_existing.reg"));
        CHECK_FALSE(jbr::reg::Manager::exist("./will_not_be_created.reg"));
    }

    SUBCASE("Target register path already exist.")
    {
        jbr::Register   reg1 = jbr::reg::Manager::create("./already_exist.reg");
        jbr::Register   reg2 = jbr::reg::Manager::create("./this_one_exist.reg");
        std::string     msg;

        try {
            reg1->copy("./this_one_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy the register ./already_exist.reg. Target path already have a register existing : ./this_one_exist.reg.");
        jbr::reg::Manager::destroy(reg1);
        jbr::reg::Manager::destroy(reg2);
    }

    SUBCASE("Copy to myself.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./myself.reg");
        std::string     msg;

        try {
            reg->copy("./myself.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy the register ./myself.reg. Target path already have a register existing : ./myself.reg.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Invalid copy to a not existing directory.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_to_directory.reg");
        bool            wasExceptionRaised = false;
        std::string     msg;

        try {
            reg->copy("./invalid/impossible.reg");
        }
        catch (jbr::reg::exception &) {
            wasExceptionRaised = true;
        }
        CHECK(wasExceptionRaised);
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Try to copy a invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_copy.reg");
        std::ofstream   regInvalid("./invalid_copy.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            reg->copy("should_not_work.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_copy.reg");
    }

    SUBCASE("Copy a register without copy right.")
    {
        jbr::Register       reg = jbr::reg::Manager::create("./copy_without_copy_right.reg",
                                                            jbr::reg::Rights(true, true, true, false, true, true));
        std::string         msg;

        try {
            reg->copy("./should_not_work.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy the register './copy_without_copy_right.reg' without copy and read right.");
        CHECK_FALSE(jbr::reg::Manager::exist("./should_not_work.reg"));
        std::filesystem::remove("./copy_without_copy_right.reg");
    }

    SUBCASE("Copy a register without read right.")
    {
        jbr::Register       reg = jbr::reg::Manager::create("./copy_without_copy_right.reg",
                                                            jbr::reg::Rights(false, true, true, true, true, true));
        std::string         msg;

        try {
            reg->copy("./should_not_work.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy the register './copy_without_copy_right.reg' without copy and read right.");
        CHECK_FALSE(jbr::reg::Manager::exist("./should_not_work.reg"));
        std::filesystem::remove("./copy_without_copy_right.reg");
    }

}
