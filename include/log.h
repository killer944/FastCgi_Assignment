#include<stdio.h>
#include<stdlib.h>

void logger(char *msg,char *src,int line){
    FILE *fp;
    fp = fopen("data.log", "a");
    if(fp==NULL){
        printf("Error opening file/n");
        exit(1);
    }
    fprintf(fp,"%s:%s:%d:",msg,src,line);
    fclose(fp);
}
