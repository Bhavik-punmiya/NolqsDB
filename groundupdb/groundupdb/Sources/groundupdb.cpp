#include "groundupdb.h"

GroundUpDB::GroundUpDB() {
    // Constructor
}

Database GroundUpDB::createEmptyDB(const std::string& dbname) {
    return Database::createEmptyDB(dbname);
}

Database GroundUpDB::loadDB(const std::string& dbname) {
    return Database::load(dbname);
}