//
// Created by lupusanay on 05.01.18.
//

#ifndef HIGHLOAD_SERVER_DATA_H
#define HIGHLOAD_SERVER_DATA_H

#include "sqlite3.h"
#include <iostream>

using namespace std;

class Data {

public:
    Data();

    string getAll(string tableName);

    string getByID(string tableName, string id);

    string addRow(string tableName, string data);

    string update(string tableName, string id, string data);

    string deleteRow(string tableName, string id);
};


#endif //HIGHLOAD_SERVER_DATA_H
