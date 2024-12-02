#include "database.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

Database::Database(std::string dbname, std::string fullpath) : m_name(dbname), m_fullpath(fullpath) {
    // Constructor
}

Database Database::createEmptyDB(std::string dbname) {
    std::string basedir(".groundupdb");
    if (!fs::is_directory(basedir)) {
        fs::create_directory(basedir);
    }

    std::string dbfolder(basedir + "/" + dbname);
    if (!fs::is_directory(dbfolder)) {
        fs::create_directory(dbfolder);
    }

    return Database(dbname, dbfolder);
}


Database Database::load(std::string dbname){
    std::string basedir(".groundupdb");
    std::string dbfolder(basedir + "/" + dbname);

    return Database(dbname, dbfolder);
}

void Database::setKeyValue(std::string key, std::string value) {
    std::ofstream os;
    os.open(m_fullpath + "/" + key + "_string.kv", std::ios::out | std::ios::trunc);
    os << value;
    os.close();
}

std::string Database::getKeyValue(std::string key) {
    std::ifstream is(m_fullpath + "/" + key + "_string.kv");
    if (!is.is_open()) {
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



std::string Database::getDirectory(void) {
    return m_fullpath;
}

void Database::destroy(void) {
    if (fs::exists(m_fullpath)) {
        fs::remove_all(m_fullpath);
    }
}
