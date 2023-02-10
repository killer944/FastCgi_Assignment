#include <fcgiapp.h>
#include <stdio.h>
#include <string.h>
#include "connect.h"
#include "memcache.h"
#include "seperater.h"

int main()
{

    FCGX_Init();
    FCGX_Request Request;
    FCGX_InitRequest(&Request, 0, 0);
    init_mem();

    while (FCGX_Accept_r(&Request) >= 0)
    {
        printf("Request Accepted\n");

        char *Path = FCGX_GetParam("QUERY_STRING", Request.envp);

        char **var = seperater(Path);
        char *link1 = var[2];
        FCGX_FPrintF(Request.out, "%s%s%d", var[2], var[0], strlen(link1));

        if (strlen(link1) == 0)
        {
            if (search_mem(var[0]) != NULL)
            {

                char *link = search_mem(var[0]);
                FCGX_FPrintF(Request.out, "HTTP/1.1 302\r\nLocation: %s\r\n\r\n", link);
            }
            else if (search_mem(var[0]) == NULL && search_db(var[0]) != NULL)
            {

                char *link = search_db(var[0]);
                insert_mem(var[0], link);
                FCGX_FPrintF(Request.out, "HTTP/1.1 302\r\nLocation: %s\r\n\r\n", link);
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
            insert_mem(var[0], var[2]);
            insert_db(var[0], var[2]);
            FCGX_FPrintF(Request.out, "HTTP/1.1 302\r\nLocation: %s\r\n\r\n", var[2]);
        }
        FCGX_Finish_r(&Request);
    }

    return 0;
}