//!
//! @file set_test.cpp
//! @author jbruel
//! @date 25/08/20
//!

#include <jbr/reg/Manager.hpp>
#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <doctest.h>
#include <fstream>

TEST_CASE("jbr::reg::Instance::set")
{

    SUBCASE("Basic set.")
    {
        jbr::Register   reg = jbr::reg::Manager::create("./set.reg");

        reg->set(jbr::reg::Variable("K", "V"));
    }

}
