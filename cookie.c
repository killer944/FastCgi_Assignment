#include <stdio.h>
#include <string.h>
#include <fcgi_stdio.h>
#include <libmemcached/memcached.h>
#include <libmemcached-1.0/memcached.h>
#include <db_operations.h>
#include <string.h>
#include <log.h>
#include <cookie.h>

int get_cookie(FCGX_Request *request,const QUERY_PARAM *query_params){
		char *cookies=FCGX_GetParam("HTTP_COOKIE",(request)->envp);

		if(NULL!=cookies){
			return COOKIE_PRESENT;
		}else{
			log_trace("COOKIE_ABSENT");
			return COOKIE_ABSENT;
		}

}


void set_cookie(FCGX_Request *request,const char* key,const char* value,const int COOKIE_TIMEOUT){
	FCGX_FPrintF((*request).out,"Set-Cookie: %s = %s;Max-Age = %d\r\n",key,value,COOKIE_TIMEOUT);
	log_trace("COOKIE DROPPED");
}