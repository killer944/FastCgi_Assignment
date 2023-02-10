#include<string.h>
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
    // printf("%s",user);
    strcpy(it[i].username,user);
    strcpy(it[i].homepage,url);
    // printf("%s",it[i].homepage);
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