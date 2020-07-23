//!
//! @file isMovable_test.cpp
//! @author jbruel
//! @date 23/07/20
//!

#include <jbr/Register.hpp>
#include <jbr/reg/Manager.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <filesystem>
#include <fstream>

TEST_CASE("jbr::reg::Instance::isMovable")
{

    SUBCASE("Valid movable register.")
    {
        jbr::Register reg = jbr::reg::Manager::create("./valid_movable.reg");

        CHECK(reg->isMovable());
        jbr::reg::Manager::destroy(reg);
    }

    SUBCASE("Not movable register.")
    {
        jbr::Register       reg1 = jbr::reg::Manager::create("./valid_not_movable1.reg", jbr::reg::Rights(true, true, true, true, false, true));
        jbr::Register       reg2 = jbr::reg::Manager::create("./valid_not_movable2.reg", jbr::reg::Rights(false, true, true, true, true, true));
        jbr::Register       reg3 = jbr::reg::Manager::create("./valid_not_movable3.reg", jbr::reg::Rights(true, false, true, true, true, true));

        CHECK(!reg1->isMovable());
        CHECK(!reg2->isMovable());
        CHECK(!reg2->isMovable());
        jbr::reg::Manager::destroy(reg1);
        jbr::reg::Manager::destroy(reg3);
        std::filesystem::remove("./valid_not_movable2.reg");
    }

    SUBCASE("Invalid register.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./invalid_movable.reg");
        std::ofstream   regInvalid("./invalid_movable.reg");
        std::string     msg;

        regInvalid << "spdokpod \n <jdspssjd>><<<>>dofkdf\n";
        regInvalid.close();
        try {
            (void)reg->isMovable();
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Parsing error while loading the register file, error code : 15.");
        std::filesystem::remove("./invalid_movable.reg");
    }

}
