#include "database.h"
#include "extension/extdatabase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace groundupdb;
using namespace groundupdbext;

// 'Hidden' Database::Impl class here
class EmbeddedDatabase ::Impl : public IDatabase
{
public:
    Impl(std::string dbname, std::string fullpath);
    ~Impl();

    std::string getDirectory(void);

    // management functions
    static const  std::unique_ptr<IDatabase> createEmptyDB(std::string dbname);
    static const  std::unique_ptr<IDatabase> load(std::string dbname);
    void destroy(void);

    // Key-Value use cases
    void setKeyValue(std::string key, std::string value);
    std::string getKeyValue(std::string key);

private:
    std::string m_name;
    std::string m_fullpath;
};

EmbeddedDatabase::Impl::Impl(std::string dbname, std::string fullpath) : m_name(dbname), m_fullpath(fullpath)
{
    ;
}

EmbeddedDatabase::Impl::~Impl()
{
    ;
}

// Management functions

const std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::createEmptyDB(std::string dbname)
{
    std::string basedir(".groundupdb");
    if (!fs::is_directory(basedir))
    {
        fs::create_directory(basedir);
    }

    std::string dbfolder(basedir + "/" + dbname);
    if (!fs::is_directory(dbfolder))
    {
        fs::create_directory(dbfolder);
    }

    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}

const  std::unique_ptr<IDatabase> EmbeddedDatabase::Impl::load(std::string dbname)
{
    std::string basedir(".groundupdb");
    std::string dbfolder(basedir + "/" + dbname);
    return std::make_unique<EmbeddedDatabase::Impl>(dbname, dbfolder);
}

void EmbeddedDatabase::Impl::setKeyValue(std::string key, std::string value)
{
    std::ofstream os;
    os.open(m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

std::string EmbeddedDatabase::Impl::getKeyValue(std::string key)
{
    std::ifstream is(m_fullpath + "/" + key + "_string.kv");
    if (!is.is_open())
    {
        throw std::runtime_error("Key not found: " + key);
    }

    std::string value;
    is.seekg(0, std::ios::end);
    value.reserve(is.tellg());
    is.seekg(0, std::ios::beg);

    value.assign((std::istreambuf_iterator<char>(is)),
                 std::istreambuf_iterator<char>());

    return value;
}

std::string EmbeddedDatabase::Impl::getDirectory(void)
{
    return m_fullpath;
}

void EmbeddedDatabase::Impl::destroy(void)
{
    if (fs::exists(m_fullpath))
    {
        fs::remove_all(m_fullpath);
    }
}

// Embedded Database
EmbeddedDatabase::EmbeddedDatabase(std::string dbname, std::string fullpath)
    : mImpl(std::make_unique<EmbeddedDatabase::Impl>(dbname, fullpath))
{
    ;
}

EmbeddedDatabase::~EmbeddedDatabase()
{
    ;
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::createEmptyDB(std::string dbname)
{
    return EmbeddedDatabase::Impl::createEmptyDB(dbname);
}

const std::unique_ptr<IDatabase> EmbeddedDatabase::load(std::string dbname)
{
    return EmbeddedDatabase::Impl::load(dbname);
}

void EmbeddedDatabase::setKeyValue(std::string key, std::string value)
{
    mImpl->setKeyValue(key, value);
}

std::string EmbeddedDatabase::getKeyValue(std::string key)
{
    return mImpl->getKeyValue(key);
}

std::string EmbeddedDatabase::getDirectory()
{
    return mImpl->getDirectory();
}

void EmbeddedDatabase::destroy(void)
{
    mImpl->destroy();
}
