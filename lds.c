#include<string.h>
#include<stdio.h>
#include "/home/shashank/Desktop/phase1/seperater.h"
struct database
{
    int id;
    char username[100];
    char homepage[1000];
} it[50];
static int i=0;

 //localhost/fcgi?uname=sahil&ran=0.96&url=https://www.google.com
void add(char **var){
    it[i].id=i;
    char *user=var[0];
    char *url=var[2];
    strcpy(it[i].username,user);
    strcpy(it[i].homepage,url);
    i++;
}
char* search(char *var){
    for(int j=0;j<50;j++){
        if(strcmp(it[j].username,var)==0){
            return it[j].homepage;
        }
    }
    return "User Not Found";
}

int main()
{
    char *path="localhost/fcgi?uname=sahil&ran=0.96&url=https://www.google.com";
    char **var=seperater(path);
   add(var);
   printf("%s",search(var[0]));
    return 0;
}