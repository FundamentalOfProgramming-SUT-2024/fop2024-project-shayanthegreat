#ifndef CONNECT_H
#define CONNECT_H
#include "main.h"

bool is_new(char *user_name);
void Create_user(Userinfo* userinfo);
void Fetch_user(char* user_name);
void Update_user(Userinfo* userinfo);

Userinfo Fetch_user2(char* user_name);




#endif