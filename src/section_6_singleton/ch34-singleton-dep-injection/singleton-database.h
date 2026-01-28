/**
 *    @file singleton-database.h
 *    @brief Chapter 33: Testeability Issues
 *    @author rouxfederico@gmail.com
 */

#pragma once

#include <fstream>  // IWYU pragma: keep
#include <map>
#include <ostream>  // IWYU pragma: keep
#include <sstream>  // IWYU pragma: keep
#include <string>
#include <vector>

class Database {
   public:
    virtual int getPopulation(const std::string& city) = 0;
};

class SingletonDatabase : public Database {
   private:
    SingletonDatabase();
    std::map<std::string, int> capitals_;

   public:
    // deleting copy constructor and assignment:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    // for clang-tidy compliance:
    SingletonDatabase(SingletonDatabase&&) = default;
    SingletonDatabase& operator=(SingletonDatabase&&) = default;
    ~SingletonDatabase() = default;

    static SingletonDatabase& get();

    int getPopulation(const std::string& city) override;

    void print();
};

struct SingletonRecordFinder {
    int totalPopulation(std::vector<std::string> cities);
};

struct ConfigurableRecordFinder {
    Database& db;

    ConfigurableRecordFinder(Database& db) : db(db) {}
    int totalPopulation(std::vector<std::string> city);
};
