#include "base/filesystem/file.h"
#include "libsqlite.h"

struct table_row_t
{
    int             id;
    std::string     name;
    int             age;
    std::string     address;
    double          salary;
};

static const table_row_t table_row[] = 
{
    { 0, "Paul",  32, "California", 20000.00 }, 
    { 1, "Allen", 25, "Texas",      15000.00 }, 
    { 2, "Teddy", 23, "Norway",     20000.00 }, 
    { 3, "Mark",  25, "Rich-Mond",  65000.00 }  
};

void test_sqlite(void)
{
    SQLiteDB db;

    const char * db_path = "./test.db";
    Stupid::Base::stupid_unlink_safe(db_path);
    bool a = db.create(db_path);

    bool b = db.is_open();

    const char * create_table_sql = 
        "CREATE TABLE COMPANY("             \
        "ID INT PRIMARY KEY     NOT NULL,"  \
        "NAME           TEXT    NOT NULL,"  \
        "AGE            INT     NOT NULL,"  \
        "ADDRESS        CHAR(50),"          \
        "SALARY         REAL );";
    bool c = db.execute("create table", create_table_sql);

    {
        printf("insert data all:\n");
        const char * insert_sql = 
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) VALUES (?, ?, ?, ?, ?)";

        SQLiteWriter writer(db.create_writer(insert_sql));
        bool x = writer.good();
        bool y = db.begin_transaction();
        for (int index = 0; index < sizeof(table_row) / sizeof(table_row[0]); ++index)
        {
            const table_row_t & row = table_row[index];
            printf("    %d: [%4d %10s %6d %12s %.2f]\n", index, row.id, row.name.c_str(), row.age, row.address.c_str(), row.salary);
            writer.reset();
            writer.bind(0, row.id);
            writer.bind(1, row.name);
            writer.bind(2, row.age);
            writer.bind(3, row.address);
            writer.bind(4, row.salary);
            writer.write();
        }
        bool z = db.end_transaction();
    }

    {
        printf("select data all:\n");
        const char * select_sql = "SELECT * from COMPANY";
        SQLiteReader reader(db.create_reader(select_sql));
        bool x = reader.good();
        while (reader.read())
        {
            table_row_t row;
            reader.column(0, row.id);
            reader.column(1, row.name);
            reader.column(2, row.age);
            reader.column(3, row.address);
            reader.column(4, row.salary);
            printf("    [%4d %10s %6d %12s %.2f]\n", row.id, row.name.c_str(), row.age, row.address.c_str(), row.salary);
        }
    }

    {
        printf("update data all:\n");
        const char * update_sql = "UPDATE COMPANY set SALARY = SALARY+? where ID=?";

        SQLiteWriter writer(db.create_writer(update_sql));
        bool x = writer.good();
        bool y = db.begin_transaction();
        for (int index = 0; index < sizeof(table_row) / sizeof(table_row[0]); ++index)
        {
            printf("    %d update...\n", index);
            writer.reset();
            writer.bind(0, 10000.00 + 1000.00 * index);
            writer.bind(1, index);
            writer.write();
        }
        bool z = db.end_transaction();
    }

    {
        printf("select data single:\n");
        const char * select_sql = "SELECT * from COMPANY where id=?";
        SQLiteReader reader(db.create_reader(select_sql));
        bool x = reader.good();
        for (int index = 0; index < sizeof(table_row) / sizeof(table_row[0]); ++index)
        {
            reader.reset();
            reader.bind(0, index);
            if (reader.read())
            {
                table_row_t row;
                reader.column(0, row.id);
                reader.column(1, row.name);
                reader.column(2, row.age);
                reader.column(3, row.address);
                reader.column(4, row.salary);
                printf("    %d: [%4d %10s %6d %12s %.2f]\n", index, row.id, row.name.c_str(), row.age, row.address.c_str(), row.salary);
            }
        }
    }

    db.close();
}

int main(int argc, char * argv[])
{
    test_sqlite();
    return (0);
}
