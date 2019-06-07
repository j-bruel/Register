//!
//! @file register_copy_test.cpp
//! @author jbruel
//! @date 07/06/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("Register::copy")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.copy("", "./empty.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To copy a register the copied register path must not be empty.");
        try {
            mRegister.copy("./empty.reg", "");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To copy a register the new register path must not be empty.");
    }

    SUBCASE("copy one")
    {
        mRegister.create("./copy.reg");
        CHECK_NOTHROW(mRegister.copy("./copy.reg", "./copied.reg"));
        CHECK(mRegister.exist("./copied.reg"));
        CHECK(mRegister.exist("./copy.reg"));
        mRegister.destroy("./copy.reg");
        mRegister.destroy("./copied.reg");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.copy("./not_exist.reg", "./new.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy a not existing register : ./not_exist.reg.");
        CHECK(!mRegister.exist("./not_exist.reg"));
        CHECK(!mRegister.exist("./new.reg"));
    }

    SUBCASE("target register already exist")
    {
        std::string msg;

        mRegister.create("./target.reg");
        mRegister.create("./from.reg");
        try {
            mRegister.copy("./from.reg", "./target.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy the register ./from.reg. Target path already have a register existing : ./target.reg.");
        CHECK(mRegister.exist("./target.reg"));
        CHECK(mRegister.exist("./from.reg"));
        mRegister.destroy("./target.reg");
        mRegister.destroy("./from.reg");
    }

    SUBCASE("invalid copy")
    {
        std::string msg;

        mRegister.create("./invalid.reg");
        try {
            mRegister.copy("./invalid.reg", "./unknown/to.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to copy this next register : ./invalid.reg to : ./unknown/to.reg. Error code : 2, why : No such file or directory.");
        mRegister.destroy("./invalid.reg");
    }

    SUBCASE("corrupt")
    {
        std::ofstream   reg("./corrupt.reg");
        std::string     msg;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            mRegister.copy("./corrupt.reg", "./not_corrupt.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./corrupt.reg");
    }

}
