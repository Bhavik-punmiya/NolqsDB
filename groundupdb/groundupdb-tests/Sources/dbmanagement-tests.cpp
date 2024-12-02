#include "tests.h"

#include <filesystem>
#include <string>
#include <iostream>
#include "groundupdb.h"

namespace fs = std::filesystem;

TEST_CASE("db-create", "[createEmptyDB]") {

    // Story:-
    //   [Who]   As a database administrator
    //   [What]  I need to create a new empty database
    //   [Value] So I can later store and retrieve data

    SECTION("Default settings") {
        std::string dbname("myemptydb");

        // Create a new empty database
        Database db(GroundUpDB::createEmptyDB(dbname));

        // Verify that the database directory is created
        REQUIRE(fs::is_directory(db.getDirectory()));

        // Check that the directory is empty
        auto it = fs::directory_iterator(db.getDirectory());
        REQUIRE(it == fs::end(it));

        // Destroy the database
        db.destroy();

        // Verify that the database directory is deleted
        REQUIRE(!fs::exists(db.getDirectory()));
    }

    
}

TEST_CASE("Load an existing database", "[loadDB]") {

    // Story:-
    //   [Who]   As a database user
    //   [What]  I need to create a reference to an existing database
    //   [Value] So I can later store and retrieve data

    SECTION("Default settings") {
        std::string dbname("myemptydb");
        Database db(GroundUpDB::createEmptyDB(dbname));

        Database db2(GroundUpDB::loadDB(dbname)); 

        // We know we have been successful when:-
        //  1. We have a valid database reference returned
        //      - No test -> The above would have errored
        //  2. The DB has a folder that exists on the file system
        REQUIRE(fs::is_directory(fs::status(db2.getDirectory()))); 
        // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/is_directory

        //  3. The database folder is empty (no database files yet)
        const auto& p = fs::directory_iterator(db2.getDirectory());
        REQUIRE(p == end(p)); // i.e., no contents as iterator is at the end already
        // C++17 Ref: https://en.cppreference.com/w/cpp/filesystem/directory_iterator

        // Clear out the DB
        db2.destroy();
        REQUIRE(!fs::exists(fs::status(db2.getDirectory())));
    }
}

