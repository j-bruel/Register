//!
//! @file register_apply_rights_test.cpp
//! @author jbruel
//! @date 15/07/19
//!

#include <jbr/Register.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("Register::applyRights")
{
    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string         msg;
        jbr::reg::Rights    rights;

        try {
            mRegister.applyRights("", rights);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "To apply new register rights, the path must not be empty.");
    }

    SUBCASE("not existing")
    {
        std::string         msg;
        jbr::reg::Rights    rights;

        try {
            mRegister.applyRights("./not_exist.reg", rights);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to apply new register rights from a not existing register : ./not_exist.reg.");
        CHECK(!mRegister.exist("./not_exist.reg"));
    }


    SUBCASE("applyRights after create")
    {
        jbr::reg::Rights    rights;
        jbr::reg::Rights    rightsOut;

        rights.mDestroy = true;
        rights.mWrite = true;
        rights.mMove = false;
        rights.mRead = true;
        rights.mCopy = false;
        rights.mOpen = false;
        mRegister.create("./rights.reg");
        rightsOut = mRegister.rights("./rights.reg");
        CHECK(mRegister.exist("./rights.reg"));
        CHECK(rightsOut.mDestroy);
        CHECK(rightsOut.mWrite);
        CHECK(rightsOut.mMove);
        CHECK(rightsOut.mRead);
        CHECK(rightsOut.mCopy);
        CHECK(rightsOut.mOpen);
        CHECK_NOTHROW(mRegister.applyRights("./rights.reg", rights));
        rightsOut = mRegister.rights("./rights.reg");
        CHECK(rightsOut.mDestroy);
        CHECK(rightsOut.mWrite);
        CHECK(!rightsOut.mMove);
        CHECK(rightsOut.mRead);
        CHECK(!rightsOut.mCopy);
        CHECK(!rightsOut.mOpen);
        mRegister.destroy("./rights.reg");
    }

    SUBCASE("same rights")
    {
        jbr::reg::Rights    rightsOut;
        jbr::reg::Rights    rights;

        mRegister.create("./same_rights.reg");
        mRegister.applyRights("./same_rights.reg", rights);
        rightsOut = mRegister.rights("./same_rights.reg");
        CHECK(mRegister.exist("./same_rights.reg"));
        CHECK(rightsOut.mDestroy);
        CHECK(rightsOut.mWrite);
        CHECK(rightsOut.mMove);
        CHECK(rightsOut.mRead);
        CHECK(rightsOut.mCopy);
        CHECK(rightsOut.mOpen);
        mRegister.destroy("./same_rights.reg");
    }

    SUBCASE("corrupt")
    {
        std::ofstream       reg("./corrupt.reg");
        std::string         msg;
        jbr::reg::Rights    rights;

        reg << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        reg.close();
        try {
            mRegister.applyRights("./corrupt.reg", rights);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./corrupt.reg");
    }

    SUBCASE("right apply without write rights")
    {
        jbr::reg::Rights    rights;
        jbr::reg::Rights    rightsAll;
        std::string         msg;

        rights.mWrite = false;
        mRegister.create("./apply_rights_without_write_right.reg", rights);
        try {
            mRegister.applyRights("./apply_rights_without_write_right.reg", rightsAll);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./apply_rights_without_write_right.reg is not writable. Please check the register rights, write must be allow.");
        std::filesystem::remove("./apply_rights_without_write_right.reg");
    }

}
