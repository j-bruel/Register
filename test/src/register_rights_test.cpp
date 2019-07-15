//!
//! @file register_rights_test.cpp
//! @author jbruel
//! @date 15/07/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("Register::rights")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        try {
            mRegister.rights("");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To get register rights, the path must not be empty.");
    }

    SUBCASE("right with create")
    {
        jbr::reg::Rights    rights;
        jbr::reg::Rights    rightsOut;

        rights.mDestroy = true;
        rights.mWrite = true;
        rights.mMove = false;
        rights.mRead = true;
        rights.mCopy = false;
        rights.mOpen = false;
        mRegister.create("./rights.reg", rights);
        rightsOut = mRegister.rights("./rights.reg");
        CHECK(mRegister.exist("./rights.reg"));
        CHECK(rightsOut.mDestroy);
        CHECK(rightsOut.mWrite);
        CHECK(!rightsOut.mMove);
        CHECK(rightsOut.mRead);
        CHECK(!rightsOut.mCopy);
        CHECK(!rightsOut.mOpen);
        mRegister.destroy("./rights.reg");
    }

    SUBCASE("not existing")
    {
        std::string msg;

        try {
            mRegister.rights("./not_exist.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to extract register rights from a not existing register : ./not_exist.reg.");
        CHECK(!mRegister.exist("./not_exist.reg"));
    }

    SUBCASE("default rights")
    {
        jbr::reg::Rights    rightsOut;

        mRegister.create("./rights.reg");
        rightsOut = mRegister.rights("./rights.reg");
        CHECK(mRegister.exist("./rights.reg"));
        CHECK(rightsOut.mDestroy);
        CHECK(rightsOut.mWrite);
        CHECK(rightsOut.mMove);
        CHECK(rightsOut.mRead);
        CHECK(rightsOut.mCopy);
        CHECK(rightsOut.mOpen);
        mRegister.destroy("./rights.reg");
    }

    SUBCASE("corrupt")
    {
        std::ofstream   reg("./corrupt.reg");
        std::string     msg;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            mRegister.rights("./corrupt.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./corrupt.reg");
    }

    SUBCASE("right extract without read rights")
    {
        jbr::reg::Rights    rights;
        jbr::reg::Rights    rightsOut;
        std::string         msg;

        rights.mRead = false;
        mRegister.create("./without_read_rights.reg", rights);
        try {
            rightsOut = mRegister.rights("./without_read_rights.reg");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./without_read_rights.reg is not readable. Please check the register rights, read must be allow.");
        std::filesystem::remove("./without_read_rights.reg");
    }

}
