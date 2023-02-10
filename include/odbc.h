#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
SQLHENV env;
// connection handle
SQLHDBC dbc;
SQLHSTMT stmt;
SQLRETURN ret;
SQLCHAR ans1[100];
void initodbc(){
    /* Allocate an environment handle */
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (!SQL_SUCCEEDED(ret))
    {
        fprintf(stderr, "Error allocating environment handle\n");
        
    }

    /* Set the ODBC version to use */
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
    if (!SQL_SUCCEEDED(ret))
    {
        fprintf(stderr, "Error setting ODBC version\n");
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        
    }

    /* Allocate a connection handle */
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        fprintf(stderr, "Error allocating connection handle\n");
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        
    }

    /* Connect to the database */
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DRIVER={MySQL};SERVER=localhost;DATABASE=sample;UID=root;PWD=Gomu@2000;", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret))
    {
        fprintf(stderr, "Error connecting to the database\n");
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        
    }
    else
    {
        printf("Database connected successfully");
    }
    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret))
    {
        printf("Error allocating a statement handle\n");
        
    }
    
}

void insertodbc(char *username,char *url){
    SQLCHAR query[1024];
    sprintf((char*)query, "INSERT INTO testdb (username,url) VALUES ('%s', '%s')", username,url);
    ret = SQLExecDirect(stmt, query, SQL_NTS);
    
    if (!SQL_SUCCEEDED(ret)) {
        printf("Error inserting data into the table\n");
        
    }
    else{
        printf("Inserted Successfully");
    }

}
char *searchodbc(char *user){
    SQLCHAR query[1024];
    sprintf((char*)query, "SELECT url FROM testdb WHERE username='%s'", user);
    ret = SQLExecDirect(stmt, query, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        printf("Error searching data into the table\n");
    
    }
    else{
        printf("Searched Successfully");
    }
    
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
    
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, ans1, sizeof(ans1), NULL);
    }
    return (char*)ans1;


}
