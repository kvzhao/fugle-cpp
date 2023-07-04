
#include "test_db.hpp"

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

int StockDBTester::RunSQLiteSample() {

    try {
        SQLite::Database database("example.db",
                                  SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
        database.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER "
                      "PRIMARY KEY, name TEXT, age INTEGER)");

        SQLite::Statement insertQuery(
            database, "INSERT INTO person (name, age) VALUES (?, ?)");
        insertQuery.bind(1, "John Doe");
        insertQuery.bind(2, 25);
        insertQuery.exec();

        SQLite::Statement selectQuery(database, "SELECT * FROM person");
        while (selectQuery.executeStep()) {
            int id = selectQuery.getColumn(0);
            std::string name = selectQuery.getColumn(1);
            int age = selectQuery.getColumn(2);

            std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age
                      << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "SQLite error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}