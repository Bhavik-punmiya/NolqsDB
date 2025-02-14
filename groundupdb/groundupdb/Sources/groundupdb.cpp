#include "groundupdb.h"
#include "extensions/extdatabase.h"

using namespace groundupdb;
using namespace groundupdbext;

GroundUpDB::GroundUpDB() {
    // Constructor
}

std::unique_ptr<IDatabase>  GroundUpDB::createEmptyDB(const std::string& dbname) {
    return EmbeddedDatabase::createEmptyDB(dbname);
}

std::unique_ptr<IDatabase> GroundUpDB::loadDB(const std::string& dbname) {
    return EmbeddedDatabase::load(dbname);
}