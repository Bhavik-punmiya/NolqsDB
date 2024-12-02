#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class Database
{
public:
    Database(std::string dbname, std::string fullpath);

    static Database createEmptyDB(std::string dbname);
    static Database load(std::string dbname);

    void destroy(void);
    std::string getDirectory(void);

    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

protected:
    std::string m_name;
    std::string m_fullpath;
};

#endif;