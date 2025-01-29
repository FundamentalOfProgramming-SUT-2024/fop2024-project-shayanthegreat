#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include<time.h>
#include<locale.h>
#include <unistd.h>

void lister(int n, char folders[100][256]);
int get_folders_in_directory(char *path, char folders[100][256]);
//Userinfo Fetch_user2(char* user_name);
#endif
