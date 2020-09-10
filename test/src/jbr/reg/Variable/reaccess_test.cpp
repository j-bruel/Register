//!
//! @file reaccess_test.cpp
//! @author jbruel
//! @date 10/09/20
//!

#include <jbr/reg/Variable.hpp>
#include <jbr/reg/exception.hpp>
#include <cstring>
#include <doctest.h>

TEST_CASE("jbr::reg::Variable::reaccess")
{

    SUBCASE("Basic update rights.")
    {
        jbr::reg::Variable  var("reaccess", "data");

        var.reaccess(jbr::reg::var::perm::Rights(true, false, false, false, true, false));

        jbr::reg::var::perm::Rights rights = var.rights();

        CHECK(rights.mRead);
        CHECK_FALSE(rights.mWrite);
        CHECK_FALSE(rights.mUpdate);
        CHECK_FALSE(rights.mRename);
        CHECK(rights.mCopy);
        CHECK_FALSE(rights.mRemove);
    }

    SUBCASE("Reaccess on same rights.")
    {
        jbr::reg::Variable  var("reaccess", "data");

        var.reaccess(jbr::reg::var::perm::Rights(true, true, true, true, true, true));

        jbr::reg::var::perm::Rights rights = var.rights();

        CHECK(rights.mRead);
        CHECK(rights.mWrite);
        CHECK(rights.mUpdate);
        CHECK(rights.mRename);
        CHECK(rights.mCopy);
        CHECK(rights.mRemove);
    }

    SUBCASE("Reaccess on same rights.")
    {
        jbr::reg::Variable  var("reaccess", "data", jbr::reg::var::perm::Rights(true, true, false, true, true, true));
        std::string         msg;

        try {
            var.reaccess(jbr::reg::var::perm::Rights(true, true, true, true, true, true));
        }
        catch (jbr::reg::exception &e) {
            msg = e.what();
        }
        CHECK(msg == "Impossible to reaccess a register variable, the 'read', 'write' and 'update' rights must be set to true.");

        jbr::reg::var::perm::Rights rights = var.rights();

        CHECK(rights.mRead);
        CHECK(rights.mWrite);
        CHECK_FALSE(rights.mUpdate);
        CHECK(rights.mRename);
        CHECK(rights.mCopy);
        CHECK(rights.mRemove);
    }

}
