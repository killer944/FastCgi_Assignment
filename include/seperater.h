// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>

// bool startsWith(const char *pre, const char *str)
// {
//     size_t lenpre = strlen(pre),
//            lenstr = strlen(str);
//     return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
// }
// char** seperater(char *q)
// {
//     char **var =(char **)malloc(3 * sizeof(char *));;
//     char uname[100];
//     char ran[100];
//     char url[300];

//     int cnt=1;
//     for (int i = 0; i < 3; i++)
//     {
//         var[i] = (char *)malloc(200 * sizeof(char));
//     }

//     //  printf("%s",q);
//     while(*q != '\0')
//     {
      
//       //localhost/fcgi?uname=sahil&ran=0.96&url=https://www.google.com
//         if(*q == '='  && cnt ==1)
//         {  
           
//             int k=0;
//             q++;
//             while(*q != '&')
//             {
//                 uname[k++] = *q ;
//                 q++;  
//                  if(*q == '\0')
//                     break; 
//             }
//             uname[k]='\0';
//             strcpy(var[0],uname);
//             //  printf("%s\n",var[0]);
            
            
//             cnt ++;

//         }

//          if(*q == '='  && cnt ==2)
//         {  
           
//             int k=0;
//             q++;
//             while(*q != '&')
//             {
                 
//                 ran[k++]=*q ;
//                 q++;  

//                  if(*q == '\0')
//                     break; 
//             }
//               ran[k]='\0';
//             strcpy(var[1],ran);
//             //  printf("%s\n",var[1]);

//             cnt ++;

//         }

//          if(*q == '='  && cnt ==3)
//         {  
             
//             int k=0;
//             q++;
//             while(*q != '&')
//             {
               
//                 url[k++]=*q ;
//                 q++;   
//                  if(*q == '\0')
//             break;
//             }

//             url[k]='\0';
//              strcpy(var[2],url);
//             //  printf("%s\n",var[2]);

//             cnt ++;

//         }
//         if(*q == '\0')break;

//          q++;

        

//     }
//     // if(cnt==2){
//     //     var[1]="\0";
//     //     var[2]="\0";

//     // }
//         return var;
  
// }

#include <stdio.h>
#include <string.h>

char **seperater(char *query_string)
{
	char uname[32];
	char forfloat[32];
	// float ran;
	char url[100];
	char *ptr = query_string;
	char **strings = (char **)malloc(3 * sizeof(char *));
	for (int i = 0; i < 3; i++)
	{
		strings[i] = (char *)malloc(200 * sizeof(char));
	}
	int i = 0;
	while (*ptr != '\0')
	{

		// uname=sahil&ran=0.3434&url=sfdfsdf

		if (*ptr == '=' && i == 0)
		{

			int j = 0;
			ptr++;
			while (*ptr != '&')
			{
				uname[j++] = *ptr;
				ptr++;
				if (*ptr == '\0')
					break;
			}
			uname[j]='\0';
			i++;
		}
		if (*ptr == '=' && i == 1)
		{
			int j = 0;
			ptr++;
			while (*ptr != '&')
			{

				forfloat[j++] = *ptr;
				ptr++;
				if (*ptr == '\0')
					break;
			}

			forfloat[j]='\0';
			i++;
		}
		if (*ptr == '=' && i == 2)
		{
			int j = 0;
			ptr++;
			while (*ptr != '\0')
			{

				url[j++] = *ptr;
				ptr++;
			}
		url[j]='\0';
			i++;
		}
		if (*ptr == '\0')
			break;
		ptr++;
	}
	strcpy(strings[0], uname);
	strcpy(strings[1], forfloat);
	strcpy(strings[2], url);
	if (i == 1)
	{
		strcpy(strings[1], "\0");
		strcpy(strings[2], "\0");
	}
	return strings;
}
