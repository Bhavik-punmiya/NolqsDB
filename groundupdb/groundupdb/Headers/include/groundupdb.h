#ifndef GROUNDUPDB_H
#define GROUNDUPDB_H


// Warning This Should only include client api files
// i.e. NOT anything within include/extensions 

#include <string>
#include "database.h"

namespace groundupdb{
    class GroundUpDB {
        public:
            GroundUpDB(); 
        
            static std::unique_ptr<IDatabase> createEmptyDB(const std::string& dbname);  // Use const reference
            static std::unique_ptr<IDatabase> loadDB(const std::string& dbname);         // Use const reference
    };
}


#endif