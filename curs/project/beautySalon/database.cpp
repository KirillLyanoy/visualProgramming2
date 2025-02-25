#include "database.h"

DataBase& DataBase::Instance()
{
    static DataBase dataBase;
    return dataBase;
}

bool DataBase::connectToDatabase(const QString& path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        return false;
    }
    return true;
}

QSqlDatabase& DataBase::getDatabase()
{
    return db;
}

DataBase::DataBase() {}

DataBase::~DataBase()
{
    db.close();
}
