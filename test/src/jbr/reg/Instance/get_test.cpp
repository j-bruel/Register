//!
//! @file get_test.cpp
//! @author jbruel
//! @date 25/08/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <fstream>
#include <doctest.h>

TEST_CASE("jbr::reg::Instance::get")
{

    SUBCASE("Basic get variable (only one variable exist).")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_get.reg");

        reg->set(jbr::reg::Variable("basic_get", "value"));
        CHECK(std::string(reg->get("basic_get").key()) == "basic_get");
        CHECK(std::string(reg->get("basic_get").read()) == "value");
        CHECK((reg->get("basic_get").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic get variable with already existed register.")
    {
        std::ofstream   regFile("./basic_get_existed_reg.reg");
        std::string     msg;

        regFile << "<register>\n"
                      "    <header>\n"
                      "        <version>1.0.0</version>\n"
                      "    </header>\n"
                      "    <body>\n"
                      "        <variable>\n"
                      "            <key>Basic set</key>\n"
                      "            <value>Basic value</value>\n"
                      "            <rights>\n"
                      "                <read>true</read>\n"
                      "                <write>true</write>\n"
                      "                <update>true</update>\n"
                      "                <rename>true</rename>\n"
                      "                <copy>true</copy>\n"
                      "                <remove>true</remove>\n"
                      "            </rights>\n"
                      "        </variable>\n"
                      "    </body>\n"
                      "</register>\n";
        regFile.close();

        jbr::Register   reg = jbr::reg::Manager::open("./basic_get_existed_reg.reg");

        CHECK(std::string(reg->get("Basic set").key()) == "Basic set");
        CHECK(std::string(reg->get("Basic set").read()) == "Basic value");
        CHECK((reg->get("Basic set").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic get variable on rights")
    {
        std::ofstream   regInvalid("./basic_get_on_rights.reg");
        std::string     msg;

        regInvalid << "<register>\n"
                      "    <header>\n"
                      "        <version>1.0.0</version>\n"
                      "    </header>\n"
                      "    <body>\n"
                      "        <variable>\n"
                      "            <key>Basic set</key>\n"
                      "            <value>Basic value</value>\n"
                      "            <rights>\n"
                      "                <read>true</read>\n"
                      "                <write>true</write>\n"
                      "                <update>false</update>\n"
                      "                <rename>true</rename>\n"
                      "                <copy>false</copy>\n"
                      "                <remove>true</remove>\n"
                      "            </rights>\n"
                      "        </variable>\n"
                      "    </body>\n"
                      "</register>\n";
        regInvalid.close();

        jbr::Register   reg = jbr::reg::Manager::open("./basic_get_on_rights.reg");

        CHECK(std::string(reg->get("Basic set").key()) == "Basic set");
        CHECK(std::string(reg->get("Basic set").read()) == "Basic value");
        CHECK((reg->get("Basic set").rights() == jbr::reg::var::perm::Rights(true, true, false, true, false, true)));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic get variable with multi set.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./multi_set.reg");

        reg->set(jbr::reg::Variable("multi_set", "value"));
        CHECK(std::string(reg->get("multi_set").key()) == "multi_set");
        CHECK(std::string(reg->get("multi_set").read()) == "value");
        CHECK((reg->get("multi_set").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        reg->set(jbr::reg::Variable("multi_set", "new value"));
        CHECK(std::string(reg->get("multi_set").key()) == "multi_set");
        CHECK(std::string(reg->get("multi_set").read()) == "new value");
        CHECK((reg->get("multi_set").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        reg->set(jbr::reg::Variable("multi_set", "value", jbr::reg::var::perm::Rights(true, true, true, false, false, true)));
        CHECK(std::string(reg->get("multi_set").key()) == "multi_set");
        CHECK(std::string(reg->get("multi_set").read()) == "value");
        CHECK((reg->get("multi_set").rights() == jbr::reg::var::perm::Rights(true, true, true, false, false, true)));
        reg->set(jbr::reg::Variable("multi_set", "value"));
        CHECK(std::string(reg->get("multi_set").key()) == "multi_set");
        CHECK(std::string(reg->get("multi_set").read()) == "value");
        CHECK((reg->get("multi_set").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic get variable with multi variables.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./multi_var.reg");

        reg->set(jbr::reg::Variable("first variable", "some data"));
        reg->set(jbr::reg::Variable("second one", "OK"));
        reg->set(jbr::reg::Variable("var", ""));
        CHECK(std::string(reg->get("first variable").read()) == "some data");
        CHECK(std::string(reg->get("second one").read()) == "OK");
        CHECK(std::string(reg->get("var").read()) == "");
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_get.reg");
        std::ofstream   regInvalid("./invalid_get.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            (void)reg->get("Basic set");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_get.reg");
    }

    SUBCASE("Invalid key section.")
    {
        std::ofstream   regFile("./invalid_key_section.reg");
        std::string     msg;

        regFile << "<register>\n"
                   "    <header>\n"
                   "        <version>1.0.0</version>\n"
                   "    </header>\n"
                   "    <body>\n"
                   "        <variable>\n"
                   "            <keyqsdqsd>Basic set</key>\n"
                   "            <vaqsdqsdlue>Basic value</value>\n"
                   "            <rights>\nsdqsdsd"
                   "                <read>trueqsdqsd</read>\n"
                   "                <write>true</write>\n"
                   "                <qsdqsd>true</update>\n"
                   "                <rename>true</rename>\n"
                   "                <copy>trueqsd</copy>\n"
                   "                <remove>true</remove>\n"
                   "            </rightsdqsds>\n"
                   "        </variable>\n"
                   "    </body>\n"
                   "</register>\n";
        regFile.close();

        try {
            jbr::Register   reg = jbr::reg::Manager::open("./invalid_key_section.reg");

            CHECK(std::string(reg->get("Basic set").key()) == "Basic set");
            CHECK(std::string(reg->get("Basic set").read()) == "Basic value");
            CHECK((reg->get("Basic set").rights() == jbr::reg::var::perm::Rights(true, true, true, true, true, true)));
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 14.");
        std::filesystem::remove("./invalid_key_section.reg");
    }

}
