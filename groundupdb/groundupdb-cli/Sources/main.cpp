#include <iostream>
#include "cxxopts.hpp"
#include "groundupdb.h"

using namespace std;

cxxopts::Options options("groundupdb-cli", "CLI For GroundUpDB");

void printUsage()
{
    cout << "Whoops Bad Config" << endl;
}

int main(int argc, char *argv[])
{
    options.add_options()("c,create", "Create a DB")("d,destroy", "Destroy a DB")("s,set", "Set a key in a DB")("g,get", "Get a key from a DB")("n,name", "Database name (required)", cxxopts::value<std::string>())("k,key", "Key to set", cxxopts::value<std::string>())("v,value", "Value to set", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);

    if (result.count("c") == 1)
    {
        if (result.count("n") == 0)
        {
            cout << "You must specify a database with name -n flag" << endl;
            printUsage();
            return 1;
        }
        std::string dbname(result["n"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase>  db = groundupdb::GroundUpDB::createEmptyDB(dbname);
        return 0;
    }
    if(result.count("d") == 1)
    {
        if (result.count("n") == 0)
        {
            cout << "You must specify a database with name -n flag" << endl;
            printUsage();
            return 1;
        }
        std::string dbname(result["n"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase>  db(groundupdb::GroundUpDB::loadDB(dbname));
        db->destroy();
        return 0;
    }

    if (result.count("s") == 1)
    {
        if (result.count("n") == 0)
        {
            cout << "You must specify a database with name -n flag" << endl;
            printUsage();
            return 1;
        }
        if (result.count("k") == 0)
        {
            cout << "You must specify a key with -k flag" << endl;
            printUsage();
            return 1;
        }
        if (result.count("v") == 0)
        {
            cout << "You must specify a value with -v flag" << endl;
            printUsage();
            return 1;
        }
        std::string dbname(result["n"].as<std::string>());
        std::string key(result["k"].as<std::string>());
        std::string value(result["v"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase>  db(groundupdb::GroundUpDB::loadDB(dbname));
        db->setKeyValue(key, value);
        return 0;
    }
    if (result.count("g") == 1)
    {
        if (result.count("n") == 0)
        {
            cout << "You must specify a database name with -n <name>" << endl;
            printUsage();
            return 1;
        }
        if (result.count("k") == 0)
        {
            cout << "You must specify a key to set with -k <name>" << endl;
            printUsage();
            return 1;
        }

        // Get key value from database
        std::string dbname(result["n"].as<std::string>());
        std::string k(result["k"].as<std::string>());
        std::unique_ptr<groundupdb::IDatabase>  db(groundupdb::GroundUpDB::loadDB(dbname));
        cout << db->getKeyValue(k) << endl;
        return 0;
    }

    cout << "No command specified" << endl;
    printUsage();
    return 1;
}