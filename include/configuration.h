#include <stdio.h>
#include <stdlib.h>
#include <fcgi_stdio.h>
#include <libconfig.h>



config_t configuration_init(const char* filename){
	config_t cfg;
	config_init(&cfg);
	config_read_file(&cfg,filename);
	return cfg;
}

// int get_cookie_timeout(config_t cfg){
// 	int cookie_timeout;
// 	config_lookup_int(&cfg,"cookie_timeout",&cookie_timeout);
// 	return cookie_timeout;
// }

int get_number_of_threads(config_t cfg){
	int number_of_threads;
	config_lookup_int(&cfg,"number_of_threads",&number_of_threads);
	return number_of_threads;
}

// int get_key_expiry_time(config_t cfg){
// 	int key_expiry_time;
// 	config_lookup_int(&cfg,"key_expiry_time",&key_expiry_time);
// 	return key_expiry_time;
// }



// char* get_db_username(config_t cfg){
// 	const char *username;
// 	config_lookup_string(&cfg,"username",&username);
// 	return (char*)username;
// }

// char* get_db_password(config_t cfg){
// 	const char *password;
// 	config_lookup_string(&cfg,"password",&password);
// 	return (char*)password;
// }