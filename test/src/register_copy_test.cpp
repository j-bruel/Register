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
        CHECK(msg.find("Impossible to copy this next register : ./invalid.reg to : ./unknown/to.reg. Error code ") != std::string::npos);
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

    SUBCASE("copy without copy rights")
    {
        jbr::reg::Rights    rights;
        std::string         msg;

        rights.mCopy = false;
        mRegister.create("./copy_without_right.reg", rights);
        try {
            mRegister.copy("./copy_without_right.reg", "./must_not_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./copy_without_right.reg is not copyable. Please check the register rights, read and copy must be allow.");
        CHECK(mRegister.exist("./copy_without_right.reg"));
        CHECK(!mRegister.exist("./must_not_exist.reg"));
        mRegister.destroy("./copy_without_right.reg");
    }

    SUBCASE("copy without read rights")
    {
        jbr::reg::Rights    rights;
        std::string         msg;

        rights.mRead = false;
        mRegister.create("./copy_without_read_right.reg", rights);
        try {
            mRegister.copy("./copy_without_read_right.reg", "./must_not_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./copy_without_read_right.reg is not copyable. Please check the register rights, read and copy must be allow.");
        CHECK(mRegister.exist("./copy_without_read_right.reg"));
        CHECK(!mRegister.exist("./must_not_exist.reg"));
        std::filesystem::remove("./copy_without_read_right.reg");
    }

}
