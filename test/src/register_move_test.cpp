//!
//! @file register_move_test.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("Register::move")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.move("", "./empty.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To move a register the reference path must not be empty.");
        try {
            mRegister.move("./empty.reg", "");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To move a register the destination path must not be empty.");
    }

    SUBCASE("move one")
    {
        mRegister.create("./move.reg");
        CHECK_NOTHROW(mRegister.move("./move.reg", "./moved.reg"));
        CHECK(!mRegister.exist("./move.reg"));
        CHECK(mRegister.exist("./moved.reg"));
        mRegister.destroy("./moved.reg");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.move("./not_exist.reg", "./new.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to move a not existing register : ./not_exist.reg.");
        CHECK(!mRegister.exist("./not_exist.reg"));
        CHECK(!mRegister.exist("./new.reg"));
    }

    SUBCASE("target register already exist")
    {
        std::string msg;

        mRegister.create("./target.reg");
        mRegister.create("./from.reg");
        try {
            mRegister.move("./from.reg", "./target.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to move the register ./from.reg. Target path already have a register existing : ./target.reg.");
        CHECK(mRegister.exist("./target.reg"));
        CHECK(mRegister.exist("./from.reg"));
        mRegister.destroy("./target.reg");
        mRegister.destroy("./from.reg");
    }

    SUBCASE("invalid move")
    {
        std::string msg;

        mRegister.create("./invalid.reg");
        try {
            mRegister.move("./invalid.reg", "./unknown/to.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg.find("Impossible to move this next register : ./invalid.reg to : ./unknown/to.reg. Error code ") != std::string::npos);
        mRegister.destroy("./invalid.reg");
    }

    SUBCASE("corrupt")
    {
        std::ofstream   reg("./corrupt.reg");
        std::string     msg;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            mRegister.move("./corrupt.reg", "./not_corrupt.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./corrupt.reg");
    }

}
