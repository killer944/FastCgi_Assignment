#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>

void insert_data(SQLHANDLE henv, SQLHANDLE hdbc, char *name, char *age, char *address) {
   SQLHANDLE hstmt;
   SQLRETURN ret;
   char query[255];

   /* Allocate statement handle */
   ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error allocating statement handle\n");
      return;
   }

   /* Prepare SQL statement */
   sprintf(query, "INSERT INTO table_name (name, age, address) VALUES ('%s', '%s', '%s')", name, age, address);
   ret = SQLPrepare(hstmt, query, SQL_NTS);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error preparing statement\n");
      SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
      return;
   }

   /* Execute SQL statement */
   ret = SQLExecute(hstmt);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error executing statement\n");
   }

   /* Free statement handle */
   SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

int main(void) {
   SQLHANDLE henv, hdbc;
   SQLRETURN ret;

   /* Allocate environment handle */
   ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error allocating environment handle\n");
      return 1;
   }

   /* Set the ODBC version environment attribute */
   ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error setting ODBC version\n");
      SQLFreeHandle(SQL_HANDLE_ENV, henv);
      return 1;
   }

   /* Allocate connection handle */
   ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
   if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
      fprintf(stderr, "Error allocating connection handle\n");
      SQLFreeHandle(SQL_HANDLE_ENV,
