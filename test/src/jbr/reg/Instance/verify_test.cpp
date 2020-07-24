//!
//! @file verify_test.cpp
//! @author jbruel
//! @date 23/07/20
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Instance::verify")
{

    SUBCASE("Verify a valid register.")
    {
        jbr::Register reg = jbr::reg::Manager::create("./valid_verify.reg");

        CHECK_NOTHROW(reg->verify());
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Verify a invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_verify.reg");
        std::string     msg;
        std::ofstream   regInvalid("./invalid_verify.reg");

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            reg->verify();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_verify.reg");
    }

    SUBCASE("Verify a not existing register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./not_existing_verify.reg");
        std::string     msg;

        jbr::reg::Manager::destroy(reg);
        try {
            reg->verify();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to load a not existing xml file : ./not_existing_verify.reg.");
    }

    SUBCASE("Verify with a null xml document.")
    {
        jbr::Register           reg = jbr::reg::Manager::create("./verify_with_null_xml_doc.reg");
        tinyxml2::XMLDocument   *xmlDocument = nullptr;
        std::string             msg;

        try {
            reg->verify(*xmlDocument);
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        jbr::reg::Manager::destroy(reg);
        CHECK(msg == "Error while extracting sub node, the parent node is null.");
    }

}
