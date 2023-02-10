#include <fcgiapp.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "seperater.h"
#include "lds.h"
int main()
{
	FCGX_Init();
	//	int Socket = FCGX_OpenSocket("127.0.0.1:2016", 1024);
	FCGX_Request Request;
	FCGX_InitRequest(&Request, 0, 0);

	while (FCGX_Accept_r(&Request) >= 0)
	{
		printf("Request Accepted\n");
		char *Path = FCGX_GetParam("QUERY_STRING",Request.envp);
		char **var = seperater(Path);
		add(var);
		char *link=search(var[0]);
		FCGX_FPrintF(Request.out, "HTTP/1.1 302\r\nLocation: %s\r\n\r\n",link);
		FCGX_Finish_r(&Request);
	}

	return 0;
}
