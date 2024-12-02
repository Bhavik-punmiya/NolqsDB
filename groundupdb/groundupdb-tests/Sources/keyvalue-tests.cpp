#include "catch.hpp"
#include "groundupdb.h"

TEST_CASE("Store and Retrive Value from Database","[setKeyValue, getKeyValue]") {

    // Story:-
    //   [Who]   As a database administrator
    //   [What]  I need to store and retrieve a key-value pair
    //   [Value] So I can later retrieve the value by key

    SECTION("Store and Retrieve") {
        std::string dbname("mydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        std::string key("mykey");
        std::string value("Some Highly Valueable Value");

        db.setKeyValue(key, value); 
        REQUIRE(value == db.getKeyValue(key));
        db.destroy();
        
    }
}