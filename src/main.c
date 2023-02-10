#include <fcgiapp.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include <pthread.h>
#include "configuration.h"
#include "connect.h"
#include "memcache.h"
#include "seperater.h"
#include "log.h"
#include "odbc.h"
#define loc "HTTP/1.1 302\r\nLocation: %s\r\n\r\n"
#define CONFIG_FILE "config.cfg"
config_t cfg;
pthread_mutex_t mutex;
// Establish environment
SQLHENV env;
// connection handle
SQLHDBC dbc;
SQLHSTMT stmt;
SQLRETURN ret;
void *Request_handler(void *iid)
{
    
    FCGX_Init();
    FCGX_Request Request;
    FCGX_InitRequest(&Request, 0, 0);

    while (FCGX_Accept_r(&Request) >= 0)
    {
        logger("----------HANDLING NEW REQUEST------------",__FILE__, __LINE__); 
        logger("Request Accepted\n", __FILE__, __LINE__);
        char *Path = FCGX_GetParam("QUERY_STRING", Request.envp);
        logger("Parsing a string\n", __FILE__, __LINE__);
        char **var = seperater(Path);
        char *link1 = var[2];
        if (strlen(link1) == 0)
        {
            if (search_mem(var[0]) != NULL)
            {
                char *link = search_mem(var[0]);
                FCGX_FPrintF(Request.out, loc, link);
            }
            else if (search_mem(var[0]) == NULL && searchodbc(var[0]) != NULL)
            {
                pthread_mutex_lock(&mutex);
                char *link = searchodbc(var[0]);
                insert_mem(var[0], link);
                pthread_mutex_unlock(&mutex);
                FCGX_FPrintF(Request.out, loc, link);
            }
            else
            {
                FCGX_FPrintF(
                    Request.out,
                    "Content-type: text/html\r\n\r\n"
                    "<h1>User not found</h1>");
            }
        }
        else
        {
            pthread_mutex_lock(&mutex);
            insert_mem(var[0], var[2]);
            insertodbc(var[0], var[2]);
            pthread_mutex_unlock(&mutex);
            FCGX_FPrintF(Request.out, loc, var[2]);
        }

        FCGX_Finish_r(&Request);
    }
    return (void *)iid;
}
int main()
{
    init_mem();
    initodbc();
    cfg=configuration_init(CONFIG_FILE);
    pthread_mutex_init(&mutex, NULL);
    int no_of_threads=get_number_of_threads(cfg);
    pthread_t th[no_of_threads];

    for (int i = 0; i < no_of_threads; i++)
    {
        int *thread_id=calloc(1,sizeof(int));
        *thread_id=i+1;
        pthread_create(th + i, NULL, Request_handler, (void *)thread_id);
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}