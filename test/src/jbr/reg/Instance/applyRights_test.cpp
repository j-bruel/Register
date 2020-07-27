//!
//! @file applyRights_test.cpp
//! @author jbruel
//! @date 27/07/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::applyRights")
{
    SUBCASE("Basic apply rights on existing register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_apply_rights.reg");

        CHECK_NOTHROW(reg->applyRights(jbr::reg::Rights(true, true, true, false, false, true)));

        jbr::reg::Rights    rights = reg->rights();

        CHECK(rights.mRead);
        CHECK(rights.mWrite);
        CHECK(rights.mOpen);
        CHECK_FALSE(rights.mCopy);
        CHECK_FALSE(rights.mMove);
        CHECK(rights.mDestroy);
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Apply rights multiple time on same register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./multiple_time_apply_rights.reg");

        CHECK_NOTHROW(reg->applyRights(jbr::reg::Rights(true, true, true, false, true, true)));
        CHECK_NOTHROW(reg->applyRights(jbr::reg::Rights(true, true, true, false, true, false)));
        CHECK_NOTHROW(reg->applyRights(jbr::reg::Rights(true, true, true, false, false, true)));

        jbr::reg::Rights    rights = reg->rights();

        CHECK(rights.mRead);
        CHECK(rights.mWrite);
        CHECK(rights.mOpen);
        CHECK_FALSE(rights.mCopy);
        CHECK_FALSE(rights.mMove);
        CHECK(rights.mDestroy);
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Apply rights without write rights.")
    {
        jbr::Register       reg = jbr::reg::Manager::create("./apply_rights_without_write_right.reg",
                                                            jbr::reg::Rights(true, false, true, true, true, true));
        std::string         msg;

        try {
            reg->applyRights(jbr::reg::Rights());
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "The register ./apply_rights_without_write_right.reg is not writable. Please check the register rights, write must be allow.");
        std::filesystem::remove("./apply_rights_without_write_right.reg");
    }

    SUBCASE("Invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_applyRights.reg");
        std::ofstream   regInvalid("./invalid_applyRights.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            reg->applyRights(jbr::reg::Rights());
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_applyRights.reg");
    }

    SUBCASE("Not existing register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./not_existing.reg");
        std::string     msg;

        std::filesystem::remove("./not_existing.reg");
        try {
            reg->applyRights(jbr::reg::Rights());
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./not_existing.reg.");
        CHECK_FALSE(jbr::reg::Manager::exist("./not_existing.reg"));
    }

}


