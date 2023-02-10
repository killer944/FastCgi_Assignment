#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>
#define query_var "INSERT INTO testdb (username,url) VALUES('%s','%s');"
#define query_search "SELECT url FROM testdb WHERE username='%s';"
static char *host = "localhost";
static char *user = "root";
static char *pass = "Gomu@2000";
static char *db   = "sample";
static char *sk = NULL;
unsigned int port = 3306;
unsigned int flags = 0;
char* ans;
void insert_db( char *username,char *link){
    MYSQL *con;
    con = mysql_init(NULL);
    if (!mysql_real_connect(con, host, user, pass, db, port, sk, flags)) {
        fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
        exit(1);
    }
    char query[1024];
    sprintf(query,query_var,username,link);
    printf("%s",query);
    if(mysql_query(con,query)){
        fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
    }
    mysql_close(con);
}
char *search_db(char *username){
    MYSQL *con;
    con = mysql_init(NULL);
    if (!mysql_real_connect(con, host, user, pass, db, port, sk, flags)) {
        fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
        exit(1);
    }
    char query[1024];
    sprintf(query,query_search,username);
    if(mysql_query(con,query)){
        fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
    }
    MYSQL_RES *res;
    MYSQL_ROW row;
    ans=(char *) malloc(10*sizeof(char *));
    res=mysql_use_result(con);
    printf("%s\n",query);
    int cnt=0;
    while((row=mysql_fetch_row(res))!=NULL){
        strcpy(ans,row[0]);
        cnt++;
    }
    mysql_free_result(res);
    mysql_close(con);
    if(cnt==0){
        return NULL;
    }
    return ans;
}

// void Update(char *user,char *link){
//     MYSQL *con;
//     con = mysql_init(NULL);
//     if (!mysql_real_connect(con, host, user, pass, db, port, sk, flags)) {
//         fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
//         exit(1);
//     }
//     char query[1024];
//     sprintf(query,"UPDATE testdb SET url='%s' where username='%s';",link,user);
//     if(mysql_query(con,query)){
//         fprintf(stderr, "Error %s (%d)", mysql_error(con), mysql_errno(con));
//     }
//     mysql_close(con);
// }