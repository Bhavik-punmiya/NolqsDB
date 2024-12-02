#ifndef GROUNDUPDB_H
#define GROUNDUPDB_H

#include <string>
#include "database.h"

class GroundUpDB {
public:
    GroundUpDB(); 

    static Database createEmptyDB(const std::string& dbname);  // Use const reference
    static Database loadDB(const std::string& dbname);         // Use const reference
};

#endif