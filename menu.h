#ifndef MENU_H
#define MENU_H
#include <ncurses.h>

char *random_pass();
void music_user();
void setting_user();
void create_popup();
bool is_valid_pass(char *c);
bool is_valid_email(char *c);
void create_user();
void login_user();
void menu_user();
void dif_user();
void champ_user();
int choose_mode();







#endif