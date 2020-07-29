//!
//! @file move_test.cpp
//! @author jbruel
//! @date 29/07/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::move")
{

    SUBCASE("Empty input path.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./empty_path.reg");
        std::string     msg;

        try {
            reg->move("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To move a register the new register path must not be empty.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("NULL input path.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./null_path.reg");
        std::string     msg;

        try {
            reg->move(nullptr);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To move a register the new register path must not be empty.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic move register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_move.reg");

        CHECK_NOTHROW(reg->move("./new_basic_move.reg"));
        CHECK_FALSE(jbr::reg::Manager::exist("./basic_move.reg"));
        CHECK(jbr::reg::Manager::exist("./new_basic_move.reg"));
        CHECK(reg->localization() == "./new_basic_move.reg");
        jbr::reg::Manager::destroy(reg);
        std::filesystem::remove("./new_basic_move.reg");
    }

    SUBCASE("Move a not existing register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./not_existing.reg");
        std::string     msg;

        std::filesystem::remove("./not_existing.reg");
        try {
            reg->move("./will_not_be_created.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./not_existing.reg.");
        CHECK_FALSE(jbr::reg::Manager::exist("./will_not_be_created.reg"));
        CHECK_FALSE(jbr::reg::Manager::exist("./not_existing.reg"));
        CHECK(reg->localization() == "./not_existing.reg");
    }

    SUBCASE("Target register path already exist.")
    {
        jbr::Register   reg1 = jbr::reg::Manager::create("./already_exist.reg");
        jbr::Register   reg2 = jbr::reg::Manager::create("./this_one_exist.reg");
        std::string     msg;

        try {
            reg1->move("./this_one_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to move the register ./already_exist.reg. Target path already have a register existing : ./this_one_exist.reg.");
        CHECK(jbr::reg::Manager::exist("./already_exist.reg"));
        CHECK(jbr::reg::Manager::exist("./this_one_exist.reg"));
        CHECK(reg1->localization() == "./already_exist.reg");
        CHECK(reg2->localization() == "./this_one_exist.reg");
        jbr::reg::Manager::destroy(reg1);
        jbr::reg::Manager::destroy(reg2);
    }

    SUBCASE("Move to myself.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./myself.reg");
        std::string     msg;

        try {
            reg->move("./myself.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(jbr::reg::Manager::exist("./myself.reg"));
        CHECK(reg->localization() == "./myself.reg");
        CHECK(msg == "Impossible to move the register ./myself.reg. Target path already have a register existing : ./myself.reg.");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Invalid move to a not existing directory.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_to_directory.reg");
        bool            wasExceptionRaised = false;
        std::string     msg;

        try {
            reg->move("./invalid/impossible.reg");
        }
        catch (jbr::reg::exception &) {
            wasExceptionRaised = true;
        }
        CHECK(wasExceptionRaised);
        CHECK(jbr::reg::Manager::exist("./invalid_to_directory.reg"));
        CHECK(reg->localization() == "./invalid_to_directory.reg");
        CHECK_FALSE(jbr::reg::Manager::exist("./invalid/impossible.reg"));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Try to move a invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_copy.reg");
        std::ofstream   regInvalid("./invalid_copy.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            reg->move("should_not_work.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        CHECK(jbr::reg::Manager::exist("./invalid_copy.reg"));
        CHECK(reg->localization() == "./invalid_copy.reg");
        CHECK_FALSE(jbr::reg::Manager::exist("./should_not_work.reg"));
        std::filesystem::remove("./invalid_copy.reg");
    }

    SUBCASE("Move a register without move right.")
    {
        jbr::Register       reg = jbr::reg::Manager::create("./move_without_move_right.reg",
                                                            jbr::reg::Rights(true, true, true, true, false, true));
        std::string         msg;

        try {
            reg->move("./should_not_work_without_move_right.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to move the register './move_without_move_right.reg' without move and read right.");
        CHECK(jbr::reg::Manager::exist("./move_without_move_right.reg"));
        CHECK(reg->localization() == "./move_without_move_right.reg");
        CHECK_FALSE(jbr::reg::Manager::exist("./should_not_work_without_move_right.reg"));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Move a register without read right.")
    {
        jbr::Register       reg = jbr::reg::Manager::create("./move_without_read_right.reg",
                                                            jbr::reg::Rights(false, true, true, true, true, true));
        std::string         msg;

        try {
            reg->move("./should_not_work_without_read_right.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to move the register './move_without_read_right.reg' without move and read right.");
        CHECK_FALSE(jbr::reg::Manager::exist("./should_not_work_without_read_right.reg"));
        CHECK(jbr::reg::Manager::exist("./move_without_read_right.reg"));
        CHECK(reg->localization() == "./move_without_read_right.reg");
        std::filesystem::remove("./move_without_read_right.reg");
    }

}
