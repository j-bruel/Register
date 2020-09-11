//!
//! @file available_test.cpp
//! @author jbruel
//! @date 25/08/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::available")
{

    SUBCASE("Check if a variable exist into a empty register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./no_var.reg");

        CHECK_FALSE(reg->available(jbr::reg::Variable("no var exist", std::string())));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Invalid register file.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_file.reg");
        std::ofstream   regInvalid("./invalid_file.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            (void)reg->available(jbr::reg::Variable("no var exist", std::string()));
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_file.reg");
    }

    SUBCASE("Not existing variable.")
    {
        std::ofstream   regStream("./not_existing_var.reg");

        regStream << "<register>\n"
               "    <header>\n"
               "        <version>1.0.0</version>\n"
               "        <rights>\n"
               "            <read>true</read>\n"
               "            <write>true</write>\n"
               "        </rights>\n"
               "    </header>\n"
               "    <body>\n"
               "        <variable>\n"
               "            <key>Another one</key>\n"
               "            <value>OK</value>\n"
               "        </variable>\n"
               "        <variable>\n"
               "            <key>Last one</key>\n"
               "            <value>Still OK</value>\n"
               "        </variable>\n"
               "    </body>\n"
               "</register>\n";
        regStream.close();

        jbr::Register   reg = jbr::reg::Manager::open("./not_existing_var.reg");

        CHECK_FALSE(reg->available(jbr::reg::Variable("no var exist", std::string())));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Basic check if a variable exist.")
    {
        std::ofstream   regStream("./existing_var.reg");

        regStream << "<register>\n"
                     "    <header>\n"
                     "        <version>1.0.0</version>\n"
                     "        <rights>\n"
                     "            <read>true</read>\n"
                     "            <write>true</write>\n"
                     "        </rights>\n"
                     "    </header>\n"
                     "    <body>\n"
                     "        <variable>\n"
                     "            <key>A variable</key>\n"
                     "            <value>OK</value>\n"
                     "        </variable>\n"
                     "    </body>\n"
                     "</register>\n";
        regStream.close();

        jbr::Register   reg = jbr::reg::Manager::open("./existing_var.reg");

        CHECK(reg->available(jbr::reg::Variable("A variable", std::string())));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Multiple check if a variable exist.")
    {
        std::ofstream   regStream("./multiple_existing_var.reg");

        regStream << "<register>\n"
                     "    <header>\n"
                     "        <version>1.0.0</version>\n"
                     "        <rights>\n"
                     "            <read>true</read>\n"
                     "            <write>true</write>\n"
                     "        </rights>\n"
                     "    </header>\n"
                     "    <body>\n"
                     "        <variable>\n"
                     "            <key>A variable</key>\n"
                     "            <value>OK</value>\n"
                     "        </variable>\n"
                     "        <variable>\n"
                     "            <key>New variable</key>\n"
                     "            <value>some data ...</value>\n"
                     "        </variable>\n"
                     "        <variable>\n"
                     "            <key>Testing</key>\n"
                     "            <value>?.. ,ksdnj dh ij s sjiu</value>\n"
                     "        </variable>\n"
                     "    </body>\n"
                     "</register>\n";
        regStream.close();

        jbr::Register   reg = jbr::reg::Manager::open("./multiple_existing_var.reg");

        CHECK(reg->available(jbr::reg::Variable("New variable", std::string())));
        CHECK_FALSE(reg->available(jbr::reg::Variable("1New variable", std::string())));
        CHECK_FALSE(reg->available(jbr::reg::Variable("test", std::string())));
        CHECK(reg->available(jbr::reg::Variable("Testing", std::string())));
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Null pointer.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./null_ptr.reg");

        CHECK_FALSE(reg->available(nullptr));
        jbr::reg::Manager::destroy(reg);
    }

}
