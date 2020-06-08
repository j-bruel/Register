//!
//! @file variable_test.cpp
//! @author jbruel
//! @date 15/07/19
//!

#include <doctest.h>
#include <jbr/Register.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <fstream>

TEST_CASE("Variable::set_get")
{

    jbr::Register   mRegister;

    SUBCASE("empty input path")
    {
        std::string msg;

        CHECK_NOTHROW(mRegister.create("empty.reg"));
        try {
            mRegister["empty.reg"].set("", "value");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to set a empty key.");
        mRegister.destroy("empty.reg");
    }

    SUBCASE("not existing register")
    {
        std::string msg;

        try {
            (void)mRegister["./not_exist.reg"].get("none");
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Register variable can not be build according a not existing register : ./not_exist.reg.");
    }

    SUBCASE("One set without rights")
    {
        mRegister.create("./one_set_without_rights.reg");
        mRegister["./one_set_without_rights.reg"].set("key", "value");

        std::ifstream   file("./one_set_without_rights.reg");
        std::string     content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        CHECK(content.find("    <body>\n"
                           "        <variable>\n"
                           "            <key>key</key>\n"
                           "            <value>value</value>\n"
                           "        </variable>\n"
                           "    </body>") != 0);
        file.close();
        mRegister.destroy("./one_set_without_rights.reg");
    }

    SUBCASE("One set with rights")
    {
        jbr::reg::var::perm::Rights   rights;

        rights.mRemove = false;
        mRegister.create("./one_set_with_rights.reg");
        mRegister["./one_set_with_rights.reg"].set("key", "value", rights);

        std::ifstream   file("./valid_var.reg");
        std::string     content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        CHECK(content.find("    <body>\n"
                           "        <variable>\n"
                           "            <key>key</key>\n"
                           "            <value>value</value>\n"
                           "            <config>\n"
                           "                <rights>\n"
                           "                    <read>true</read>\n"
                           "                    <write>true</write>\n"
                           "                    <update>true</update>\n"
                           "                    <rename>true</rename>\n"
                           "                    <copy>true</copy>\n"
                           "                    <remove>false</remove>\n"
                           "                </rights>\n"
                           "            </config>\n"
                           "        </variable>\n"
                           "    </body>") != 0);
        mRegister.destroy("./one_set_with_rights.reg");
    }

    /**
     * Tests a faire.
     *
     * Multi sets with and without rights
     * One set on already existing variable.
     * Few tests on rights handling :
     * * On register level rights.
     * * On variable level rights.
     * Errors cases handling.
     */

}
