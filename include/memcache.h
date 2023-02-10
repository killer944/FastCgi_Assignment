#include <libmemcached/memcached.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
memcached_server_st *servers = NULL;
memcached_st *memc;
memcached_return rc;
void init_mem(){
    memc=memcached_create(NULL);
    servers = memcached_server_list_append(servers, "localhost", 11211, &rc);
    rc = memcached_server_push(memc, servers);
    if (rc == MEMCACHED_SUCCESS)
        fprintf(stderr, "Added server successfully\n");
    else
        fprintf(stderr, "ERROR: %s\n", memcached_strerror(memc, rc));
}
void insert_mem(char *key,char *value){
    rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
    if (rc == MEMCACHED_SUCCESS)
        fprintf(stderr, "Key-Value Pair Created\n");
    else
        fprintf(stderr, "ERROR: %s\n", memcached_strerror(memc, rc));
}
char* search_mem(char*key){
    char *res;
    size_t value_length=200;
    uint32_t flags;
    res = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);

    if(rc!=MEMCACHED_SUCCESS){
        return NULL;
    }
    else{
        return res;
    }
}