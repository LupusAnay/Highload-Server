//
// Created by lupusanay on 05.01.18.
//

#include "Data.h"

string Data::getAll(string tableName) {
    return R"({"getAll": {"tableName":")" + tableName + R"(","status":"test" }})";
}

string Data::getByID(string tableName, string id) {
    return R"({"getByID": {"tableName":")" + tableName + R"(","id":")" + id + R"(","status":"test" }})";
}

string Data::addRow(string tableName, string data) {
    return R"({"addRow": {"tableName":")" + tableName + R"(","status":"test" }})";
}

string Data::update(string tableName, string id, string data) {
    return R"({"update": {"tableName":")" + tableName + R"(","id":")" + id + R"(","status":"test" }})";
}

string Data::deleteRow(string tableName, string id) {
    return R"({"delete": {"tableName":")" + tableName + R"(","id":")" + id + R"(","status":"test" }})";
}

Data::Data() {
    /*const char *SQL = "CREATE TABLE IF NOT EXISTS foo(a,b,c); INSERT INTO FOO VALUES(1,2,3); SELECT * FROM FOO WHERE a = 2;";

    sqlite3 *db = nullptr; // хэндл объекта соединение к БД
    char *err = nullptr;

    if (sqlite3_open("my_cosy_database.dblite", &db)) {
        fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));

    } else {
        cout << "Соединен с базой данных" << endl;
    }

    if (sqlite3_exec(db, SQL, nullptr, nullptr, &err)) {
        fprintf(stderr, "Ошибка SQL: %sn", err);
        sqlite3_free(err);
    } else {
        cout << "Данные записаны" << endl;
    }

    sqlite3_close(db);
    cout << "Дескриптор закрыт" << endl;*/
}
