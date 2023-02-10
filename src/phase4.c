#include <fcgiapp.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "connect.h"
#include "memcache.h"
#include "seperater.h"
#include "log.h"
#define loc "HTTP/1.1 302\r\nLocation: %s\r\n\r\n"

pthread_mutex_t mutex;
void *Request_handler(void *iid)
{
    int *id = (int *)iid;
    FCGX_Init();
    FCGX_Request Request;
    FCGX_InitRequest(&Request, 0, 0);

    while (FCGX_Accept_r(&Request) >= 0)
    {
        logger("Request Accepted\n",__FILE__,__LINE__);
        char *Path = FCGX_GetParam("QUERY_STRING", Request.envp);
        logger("Parsing a string\n",__FILE__,__LINE__);
        char **var = seperater(Path);
        char *link1 = var[2];
        if (strlen(link1) == 0)
        {
            if (search_mem(var[0]) != NULL)
            {
                char *link = search_mem(var[0]);
                FCGX_FPrintF(Request.out, loc, link);
            }
            else if (search_mem(var[0]) == NULL && search_db(var[0]) != NULL)
            {
                pthread_mutex_lock(&mutex);
                char *link = search_db(var[0]);
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
            insert_db(var[0], var[2]);
            pthread_mutex_unlock(&mutex);
            FCGX_FPrintF(Request.out, loc, var[2]);
        }

        FCGX_Finish_r(&Request);
    }
    return (void*)id;
}
int main()
{
    init_mem();
    pthread_mutex_init(&mutex,NULL);
    pthread_t th[100];

    for (int i = 0; i < 100; i++)
    {
        pthread_create(th+i, NULL, Request_handler, (void *)&th[i]);
        pthread_join(th[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}