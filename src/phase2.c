#include <fcgiapp.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "seperater.h"
#include "lds.h"
#include "connect.h"
int main()
{

	FCGX_Init();
	FCGX_Request Request;
	FCGX_InitRequest(&Request, 0, 0);
	while (FCGX_Accept_r(&Request) >= 0)
	{
		printf("Request Accepted\n");
		char *Path = FCGX_GetParam("QUERY_STRING",Request.envp);
		char **var = seperater(Path);
        insert_db(var[0],var[2]);
        char *link=search_db(var[0]);
		FCGX_FPrintF(Request.out, "HTTP/1.1 302\r\nLocation: %s\r\n\r\n",link);
		FCGX_Finish_r(&Request);
	}
	return 0;
}
