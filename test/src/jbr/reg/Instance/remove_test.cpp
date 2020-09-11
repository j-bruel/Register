//!
//! @file remove_test.cpp
//! @author jbruel
//! @date 11/09/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::move")
{

    SUBCASE("Basic remove.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_remove.reg");

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        reg->remove("Basic set");

        std::ifstream   ifs("basic_remove.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body/>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Multi remove.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./multi_remove.reg");

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        reg->set(jbr::reg::Variable("New data", "some data"));
        reg->set(jbr::reg::Variable("last data", "some data"));
        reg->remove("Basic set");
        reg->set(jbr::reg::Variable("Oh a new one", "some data"));
        reg->remove("last data");

        std::ifstream   ifs("multi_remove.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
                         "    <header>\n"
                         "        <version>1.0.0</version>\n"
                         "    </header>\n"
                         "    <body>\n"
                         "        <variable>\n"
                         "            <key>Oh a new one</key>\n"
                         "            <value>some data</value>\n"
                         "            <rights>\n"
                         "                <read>true</read>\n"
                         "                <write>true</write>\n"
                         "                <update>true</update>\n"
                         "                <rename>true</rename>\n"
                         "                <copy>true</copy>\n"
                         "                <remove>true</remove>\n"
                         "            </rights>\n"
                         "        </variable>\n"
                         "        <variable>\n"
                         "            <key>New data</key>\n"
                         "            <value>some data</value>\n"
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
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Remove not existing variable.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./basic_remove.reg");
        std::string     msg;

        reg->set(jbr::reg::Variable("Basic set", "Basic value"));
        try {
            reg->remove("not existing");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "No variable named 'not existing' were found into the register './basic_remove.reg'.");

        std::ifstream   ifs("basic_remove.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
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
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("No remove rights.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./no_remove_right.reg");
        std::string     msg;

        reg->set(jbr::reg::Variable("Basic set", "Basic value", jbr::reg::var::perm::Rights(true, true, true, true, true, false)));
        try {
            reg->remove("Basic set");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to remove the variable, no remove rights set.");

        std::ifstream   ifs("no_remove_right.reg");
        std::string     content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        CHECK(content == "<register>\n"
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
                         "                <remove>false</remove>\n"
                         "            </rights>\n"
                         "        </variable>\n"
                         "    </body>\n"
                         "</register>\n");
        ifs.close();
        jbr::reg::Manager::destroy(reg);
    }

}
