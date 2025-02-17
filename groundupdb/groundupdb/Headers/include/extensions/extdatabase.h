#ifndef __EXTDATABASE__H__
#define __EXTDATABASE__H__

#include "database.h"

namespace groundupdbext
{
    using namespace groundupdb;

    class EmbeddedDatabase : public IDatabase
    {
    public:
        EmbeddedDatabase(std::string dbname, std::string fullpath);
        ~EmbeddedDatabase();

        std::string getDirectory(void);

        // management functions
        static const std::unique_ptr<IDatabase> createEmptyDB(std::string dbname);
        static const std::unique_ptr<IDatabase> load(std::string dbname);
        void destroy();

        // Key-Value use cases
        void setKeyValue(std::string key, std::string value);
        std::string getKeyValue(std::string key);

        class Impl;

    private:
        std::unique_ptr<Impl> mImpl;
    };
};

#endif //!__EXTDATABASE__H__