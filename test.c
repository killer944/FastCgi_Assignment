#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void seperator(char *Path)
{
	// char **var;

	char username[100];
	char ran[20];
	char url[100];

	char *token, *sub_token;
	char *rest = Path, *sub_rest;

	// get username

	token = strtok_r(rest, "&", &rest);
	sub_rest = token;
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	strncpy(username, sub_token, sizeof(sub_token));
    printf("Username: %s",username);

	// get ran

	token = strtok_r(rest, "&", &rest);
	sub_rest = token;
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	strncpy(ran, sub_token, sizeof(ran));
    printf("Ran: %s",ran);

	// get url

	token = strtok_r(rest, "&", &rest);
	sub_rest = token;
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	sub_token = strtok_r(sub_rest, "=", &sub_rest);
	strncpy(url, sub_token, sizeof(url));
    printf("Url: %s",url);
	// strcpy(var[0],username);
	// strcpy(var[1],ran);
	// strcpy(var[2],url);
}

int main()
{
    printf("Inside main");
    char *Path="http://localhost/fcgi/uname=sahil&ran=28&url=https//www.youtube.com";
    seperator(Path);
    // printf("%s %s %s",arr[0],arr[1],arr[2]);
    return 0;
}