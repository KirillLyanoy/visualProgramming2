#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>

class DataBase
{
public:

   static DataBase& Instance();
   bool connectToDatabase(const QString& path);
   QSqlDatabase& getDatabase();

private:
    DataBase();
    ~DataBase();

    QSqlDatabase db;

    DataBase(DataBase const&) = delete;
    DataBase& operator= (DataBase const&) = delete;
};

#endif
