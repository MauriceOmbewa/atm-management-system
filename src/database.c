#include <stdio.h>
#include <sqlite3.h>

int CreateDatabase(){
    sqlite3 *db;

    int openDatabase = sqlite3_open("databse.db", &db);
    if (openDatabase != SQLITE_OK){
        printf("Error opening database: ", openDatabase);
        return 1;
    }
}