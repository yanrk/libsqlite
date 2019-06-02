/********************************************************
 * Description : sqlite db class which base on sqlite3
 * Data        : 2018-04-27 14:17:00
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * History     :
 * Copyright(C): 2013 - 2020
 ********************************************************/

#ifndef SQLITE_DB_H
#define SQLITE_DB_H


#ifdef _MSC_VER
    #define LIBSQLITE_CDECL           __cdecl
    #define LIBSQLITE_STDCALL         __stdcall
    #ifdef EXPORT_LIBSQLITE_DLL
        #define LIBSQLITE_API         __declspec(dllexport)
    #else
        #ifdef USE_LIBSQLITE_DLL
            #define LIBSQLITE_API     __declspec(dllimport)
        #else
            #define LIBSQLITE_API
        #endif // USE_LIBSQLITE_DLL
    #endif // EXPORT_LIBSQLITE_DLL
#else
    #define LIBSQLITE_CDECL
    #define LIBSQLITE_STDCALL
    #define LIBSQLITE_API
#endif // _MSC_VER

#include <cstdint>
#include <string>

struct sqlite3;
struct sqlite3_stmt;

class SQLiteReader;
class SQLiteWriter;

class LIBSQLITE_API SQLiteDB
{
public:
    SQLiteDB();
    ~SQLiteDB();

public:
    bool create(const char * path, bool overwrite = false);
    bool open(const char * path);
    bool close();

public:
    bool is_open() const;
    int error() const;
    const char * what() const;

public:
    bool execute(const char * operate, const char * sql);
    bool begin_transaction();
    bool end_transaction();

public:
    SQLiteReader create_reader(const char * sql);
    SQLiteWriter create_writer(const char * sql);

private:
    std::string                             m_path;
    sqlite3                               * m_sqlite;
};

class LIBSQLITE_API SQLiteStatement
{
public:
    SQLiteStatement();
    SQLiteStatement(sqlite3 * sqlite, const char * sql);
    SQLiteStatement(SQLiteStatement & other);
    SQLiteStatement & operator = (SQLiteStatement & other);
    SQLiteStatement(SQLiteStatement && other);
    SQLiteStatement & operator = (SQLiteStatement && other);
    ~SQLiteStatement();

public: /* field_index start from 0 */
    bool good() const;
    bool reset();
    bool bind(int field_index, int field_value);
    bool bind(int field_index, int64_t field_value);
    bool bind(int field_index, double field_value);
    bool bind(int field_index, const std::string & field_value);
    void clear();

protected:
    std::string                             m_sql;
    sqlite3                               * m_sqlite;
    sqlite3_stmt                          * m_statement;
};

class LIBSQLITE_API SQLiteReader : public SQLiteStatement
{
public:
    SQLiteReader();
    SQLiteReader(sqlite3 * db, const char * sql);

public: /* column_index start from 0 */
    bool read();
    bool column(int column_index, int & column_value);
    bool column(int column_index, int64_t & column_value);
    bool column(int column_index, double & column_value);
    bool column(int column_index, std::string & column_value);
};

class LIBSQLITE_API SQLiteWriter : public SQLiteStatement
{
public:
    SQLiteWriter();
    SQLiteWriter(sqlite3 * db, const char * sql);

public:
    bool write();
};


#endif // SQLITE_DB_H
