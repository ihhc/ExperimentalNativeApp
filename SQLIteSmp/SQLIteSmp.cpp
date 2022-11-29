#include <iostream>
#include <time.h>
#include <cstdlib>
#include "sqlite3.h"

#pragma warning(disable : 4996)

using namespace std;

int main()
{
    sqlite3* testDB = nullptr;
    sqlite3_stmt* stmt = nullptr;
    //create a database 
    if (sqlite3_open("test.db", &testDB) != SQLITE_OK)
    {
        cout << "Cannot open database";
        sqlite3_close(testDB);
        return 1;
    }

    string qr = "create table if not exists testtable(id int not null, name varchar(255) not null);";
    try
    {
        char* errmsg = NULL;
//create a table
        if (sqlite3_exec(testDB, qr.c_str(), NULL, NULL, &errmsg) != SQLITE_OK)
        {
            cout << "Error: " << errmsg;
            sqlite3_close(testDB);
            return 1;
        }
        else
        {
            cout << qr << "\n";
            time_t localtime = time(NULL);
//fill the table with data
            for (int i = 1; i <= 10; i++)
            {
                char id[4] = "";
                _itoa(i, id, 10);
                qr = "insert into testtable values (" + string(id) + ", '" + string(ctime(&localtime)) + "');";
                if (sqlite3_exec(testDB, qr.c_str(), NULL, NULL, &errmsg) != SQLITE_OK)
                    cout << "Error: " << errmsg;
                else
                    cout << qr;
            }
//change the data in the table
            qr = "update testtable set name='" + string(ctime(&localtime)) + "';";
            if (sqlite3_exec(testDB, qr.c_str(), NULL, NULL, &errmsg) != SQLITE_OK)
                cout << "Error: " << errmsg;
            else
                cout << qr;
//get all the data
            qr = "select id, name from testtable";
            if (sqlite3_prepare_v2(testDB, qr.c_str(), -1, &stmt, 0) == SQLITE_OK)
            {
                cout << "\nid " << "name \n";
                while (sqlite3_step(stmt) != SQLITE_DONE)
                    cout << sqlite3_column_int(stmt, 0) << " " << sqlite3_column_text(stmt, 1);
                sqlite3_finalize(stmt);
            }
            else
                cout << "Failed to fetch data";
            qr = "delete from testtable";
            if (sqlite3_exec(testDB, qr.c_str(), NULL, NULL, &errmsg) != SQLITE_OK)
                cout << "Error: " << errmsg;
            else
                cout << qr;
            if (errmsg)
                sqlite3_free(errmsg);
            sqlite3_close(testDB);
            return 0;
        }
    }
    catch (exception* e)
    {
        cout << e;
    }
}


