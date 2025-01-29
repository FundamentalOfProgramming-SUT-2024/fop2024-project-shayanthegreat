// IN THE NAME OF GOD!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include<time.h>
#include "menu.h"
#include "connect.h"
#include "music.h"
#include "main.h"
#include "scoreboard.h"
//#define KEY_ENTER 10

char *random_pass(){
    char random_pass[] = {'0','1','2','3','4','5','6','7','8','9','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '?', '!', '@', '#', '$', '%', '^', '&', '*'};
    int x = (rand()%9)+7;
    char* ans = (char *) malloc(x * sizeof(char));
    for(int i = 0; i < x; i++){
        *(ans+i) = random_pass[rand()%71];
    }
    return ans;
}
void music_user(){
    clear();
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-4, COLS/2-3, "Music1");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2, COLS/2-3, "Music2");
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2, COLS/2-3, "off");
    attroff(COLOR_PAIR(100));
    int cnt = 0;
    while(1){
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "Music1");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-2, COLS/2-3, "Music2");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "off");
            attroff(COLOR_PAIR(100));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-4, COLS/2-3, "Music1");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "Music2");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "off");
            attroff(COLOR_PAIR(100));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1) || (x == KEY_UP && cnt == 3)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "Music1");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "Music2");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2, COLS/2-3, "off");
            attroff(COLOR_PAIR(101));
            cnt = 2;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 0){
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-4, COLS/2-3, "Music1");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "Music2");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "off");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 1){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "Music1");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-2, COLS/2-3, "Music2");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "off");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "Music1");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "Music2");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2, COLS/2-3, "off");
                attroff(COLOR_PAIR(101));
            }
        }
    }
    if(!cnt){
        music_on(1);
    }
    else if(cnt == 1){
        music_on(2);
    }
    else{
        music_off();
    }
    menu_user();
    return ;
}
void dif_user(){
    attron(A_BOLD);
    clear();
    attron(COLOR_PAIR(85));
    mvprintw(LINES/2-4, COLS/2-3, "EASY");
    attroff(COLOR_PAIR(85));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2-2, COLS/2-3, "HARD");
    attroff(COLOR_PAIR(95));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2, COLS/2-3, "GODMODE");
    attroff(COLOR_PAIR(95));
    int cnt = 0;
    while(1){
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "EASY");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-2, COLS/2-3, "HARD");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "GODMODE");
            attroff(COLOR_PAIR(95));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-4, COLS/2-3, "EASY");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "HARD");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "GODMODE");
            attroff(COLOR_PAIR(95));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1) || (x == KEY_UP && cnt == 3)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "EASY");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "HARD");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2, COLS/2-3, "GODMODE");
            attroff(COLOR_PAIR(85));
            cnt = 2;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 0){
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-4, COLS/2-3, "EASY");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "HARD");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "GODMODE");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 1){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "EASY");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-2, COLS/2-3, "HARD");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "GODMODE");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "EASY");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "HARD");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2, COLS/2-3, "GODMODE");
                attroff(COLOR_PAIR(85));
            }
        }
    }
    if(!cnt){
        HEALTH = 85;
        MAX_HEALTH = 85;
    }
    else if(cnt == 1){
        HEALTH = 70;
        MAX_HEALTH = 70;
    }
    else{
        HEALTH = 50;
        MAX_HEALTH = 50;
    }
    attroff(A_BOLD);
    menu_user();
    return ;
}
void champ_user(){
    attron(A_BOLD);
    clear();
    attron(COLOR_PAIR(85));
    mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
    attroff(COLOR_PAIR(85));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
    attroff(COLOR_PAIR(95));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
    attroff(COLOR_PAIR(95));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
    attroff(COLOR_PAIR(95));
    int cnt = 0;
    while(1){
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
            attroff(COLOR_PAIR(95));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
            attroff(COLOR_PAIR(95));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1) || (x == KEY_UP && cnt == 3)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
            attroff(COLOR_PAIR(95));
            cnt = 2;
        }
        else if((x == KEY_DOWN && cnt == 2)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
            attroff(COLOR_PAIR(85));
            cnt = 3;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 0){
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 1){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
                attroff(COLOR_PAIR(95));
            }
            else{
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "RED/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "GOLD/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "YELLOW/BLACK");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2+2, COLS/2-3, "ORANGE/BLACK");
                attroff(COLOR_PAIR(85));
            }
        }
    }
    if(!cnt){
        CHAMP_COLOR = 95;
    }
    else if(cnt == 1){
        CHAMP_COLOR = 5;
    }
    else if(cnt == 2){
        CHAMP_COLOR = 3;
    }
    else{
        CHAMP_COLOR = 4;
    }
    attroff(A_BOLD);
    menu_user();
    return ;
}
void setting_user(){
    attron(A_BOLD);
    clear();
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
    attroff(COLOR_PAIR(100));
    int cnt = 0;
    while(1){
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
            attroff(COLOR_PAIR(100));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
            attroff(COLOR_PAIR(100));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1) || (x == KEY_UP && cnt == 3)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
            attroff(COLOR_PAIR(101));
            cnt = 2;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 0){
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 1){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "DIFFICULTY");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "MUSIC");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2, COLS/2-3, "CHAMPION COLOR");
                attroff(COLOR_PAIR(101));
            }
        }
    }
    if(!cnt){
        dif_user();
    }
    else if(cnt == 1){
        music_user();
    }
    else{
        champ_user();
    }
    attroff(A_BOLD);
    return ;
}
void create_popup() {
    attron(COLOR_PAIR(95));
    mvprintw(1, COLS/2-5, "LOST YOUR password? (y/n)");
    attroff(COLOR_PAIR(95));
    int x = getch();
    while(1){
        if(x != 'y' && x != 'n'){
            x = getch();
        }
        else{
            break;
        }
    }
    if(x == 'y'){
        mvprintw(4, COLS/2-5, "Im so generous here is your password!");
        attron(COLOR_PAIR(95));
        mvprintw(5, COLS/2-5, "%s", userinfo->user_pass);
        attroff(COLOR_PAIR(95));
        mvprintw( 6, COLS/2-5, "Press any character to escape!");
        getch();
    }
    clear();
}
bool is_valid_pass(char *c){
    int c1 = 0, c2 = 0, c3 = 0;
    for(int i = 0; i < strlen(c); i++){
        if(c[i] >= 'A' && c[i] <= 'Z')
            c1++;
        if(c[i] >= 'a' && c[i] <= 'z')
            c2++;
        if(c[i] >= '0' && c[i] <= '9')
            c3++;
    }
    return (c1 && c2 && c3);
}
bool is_valid_email(char *c){
    int cnt = 0;
    for(int i = 0; i < strlen(c); i++){
        if(c[i] == '@'){
            cnt++;
        }
    }
    if(cnt != 1){
        return 0;
    }
    int y;
    for(int i = 0; i < strlen(c); i++){
        if(c[i] == '@'){
            y = i;
        }
    }
    cnt = 0;
    for(int i = y+1; i < strlen(c); i++){
        if(c[i] == '.'){
            cnt++;
        }
    }
    if(cnt != 1){
        return 0;
    }
    if(c[strlen(c)-1] != '.'){
        return 1;
    }
    return 0;
}
void create_user(){
    attron(A_BOLD);
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Enter your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
        attroff(COLOR_PAIR(100));
        if(is_new(userinfo->user_name)){
            break;
        }
    }
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvprintw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
        attroff(COLOR_PAIR(100));
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-1, COLS/2-3, "Enter your email:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2, COLS/2-3, "%s", userinfo->user_email);
        attroff(COLOR_PAIR(100));
        if(is_valid_email(userinfo->user_email)){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
            mvprintw(LINES/2-3, COLS/2-3, "Your name:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-1, COLS/2-3, "Your email:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "%s", userinfo->user_email);
            attroff(COLOR_PAIR(100));
            break;
        }
    }
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2+1, COLS/2-3, "Generate password (press Y/N)");
    attroff(COLOR_PAIR(101));
    noecho();
    int x = getch();
    while(1){
        if(x == 'y' || x == 'n'){
            break;
        }
        else{
            x = getch();
        }
    }
    echo();
    if(x == 'n'){
        while(1){
            clear();
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
            mvprintw(LINES/2-3, COLS/2-3, "Your name:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-1, COLS/2-3, "Your email:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "%s", userinfo->user_email);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2+1, COLS/2-3, "Enter your password (it must contain a-z and A-z and 0-9):");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvscanw(LINES/2+2, COLS/2-3, "%s", userinfo->user_pass);
            attroff(COLOR_PAIR(100));
            if(is_valid_pass(userinfo->user_pass)){
                break;
            }
        }
    }
    else{
        char *newpass = random_pass();
        strcpy(userinfo->user_pass, newpass);
    }
    Create_user(userinfo);
    clear();
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
    mvprintw(LINES/2-3, COLS/2-3, "Your name:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-1, COLS/2-3, "Your email:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2, COLS/2-3, "%s", userinfo->user_email);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2+1, COLS/2-3, "Your pass:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2+2, COLS/2-3, "%s", userinfo->user_pass);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(104));
    mvprintw(1, COLS/2-3, "%s", "Press any KEY to go back to menu!");
    attroff(COLOR_PAIR(104));
    int yy = getch();
    clear();
    attroff(A_BOLD);
    menu_user();
}

void login_user(){
    if(strcmp(userinfo->user_name, "guest")){
        clear();
        return ;
    }
    attron(A_BOLD);
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Enter your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
        attroff(COLOR_PAIR(100));
        if(!is_new(userinfo->user_name)){
            break;
        }
    }
    Fetch_user(userinfo->user_name);
    
    while(1){
        clear();
        create_popup();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvprintw(LINES/2-2, COLS/2-3, "%s", userinfo->user_name);
        attroff(COLOR_PAIR(100));
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-1, COLS/2-3, "Enter your password:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        char pass[50];
        mvscanw(LINES/2, COLS/2-3, "%s", pass);
        attroff(COLOR_PAIR(100));
        if(!strcmp(pass, userinfo->user_pass)){
            break;
        }
    }
    attroff(A_BOLD);
    clear();
    attron(COLOR_PAIR(104));
    mvprintw(2, COLS/2-3, "%s", "Logged in Successfully!");
    mvprintw(1, COLS/2-3, "%s", "Press any KEY to go back to menu!");
    attroff(COLOR_PAIR(104));
    int yy = getch();
    clear();
}

void menu_user(){
    clear();
    start_color();
    init_pair(101, COLOR_BLACK, COLOR_GREEN);
    init_pair(100, COLOR_GREEN, COLOR_BLACK);
    init_pair(104, COLOR_WHITE, COLOR_BLACK);
    attron(A_BOLD);
    curs_set(0);
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2+2, COLS/2-3, "SETTING");
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2+4, COLS/2-3, "GUEST");
    attroff(COLOR_PAIR(100));
    int cnt = 0;
    while(1){
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(100));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(100));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1) || (x == KEY_UP && cnt == 3)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(100));
            cnt = 2;
        }
        else if((x == KEY_DOWN && cnt == 2) || (x == KEY_UP && cnt == 4)){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(100));
            cnt = 3;
        }
        else if(x == KEY_UP && cnt == 3){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(100));
            cnt = 2;
        }
        else if(x == KEY_DOWN && cnt == 3){
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2+2, COLS/2-3, "SETTING");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2+4, COLS/2-3, "GUEST");
            attroff(COLOR_PAIR(101));
            cnt = 4;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 0){
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+2, COLS/2-3, "SETTING");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 1){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+2, COLS/2-3, "SETTING");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+2, COLS/2-3, "SETTING");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(100));
            }
            else if(cnt == 3){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2+2, COLS/2-3, "SETTING");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(100));
            }
            else{
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-4, COLS/2-3, "CREATE NEW USER");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "LOGIN TO MY ACCOUNT");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "SCOREBOARD");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2+2, COLS/2-3, "SETTING");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(101));
            }
        }
    }
    attroff(A_BOLD);
    if(!cnt){
        create_user();
    }
    else if(cnt == 1){
        login_user();
    }
    else if(cnt == 2){
        char *directory_path = "user/";  // Current directory
        char folders[MAX_FOLDERS][MAX_NAME_LEN];
        int counters = get_folders_in_directory("user/", folders);
        lister(counters, folders);
        menu_user();
        return;
    }
    else if(cnt == 3){
        setting_user();
    }
    else if(cnt == 4){

    }
    return;
}

int choose_mode(){
    clear();
    attron(COLOR_PAIR(85));
    attron(A_BOLD);
    mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
    attroff(COLOR_PAIR(85));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
    attroff(COLOR_PAIR(95));
    attron(COLOR_PAIR(95));
    mvprintw(LINES/2, COLS/2-3, "Back");
    attroff(COLOR_PAIR(95));
    int cnt = 0;
    while(1){
        timeout(-1);
        int x = getch();
        clear();
        if((x == KEY_DOWN && cnt == 0) || (x == KEY_UP && cnt == 2)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "Back");
            attroff(COLOR_PAIR(95));
            cnt = 1;
        }
        else if((x == KEY_UP && cnt == 1)){
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
            attroff(COLOR_PAIR(85));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2, COLS/2-3, "Back");
            attroff(COLOR_PAIR(95));
            cnt = 0;
        }
        else if((x == KEY_DOWN && cnt == 1)){
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(95));
            mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
            attroff(COLOR_PAIR(95));
            attron(COLOR_PAIR(85));
            mvprintw(LINES/2, COLS/2-3, "Back");
            attroff(COLOR_PAIR(85));
            cnt = 2;
        }
        else if(x == 10){
            break;
        }
        else{
            if(cnt == 1){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "Back");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 0){
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
                attroff(COLOR_PAIR(85));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2, COLS/2-3, "Back");
                attroff(COLOR_PAIR(95));
            }
            else if(cnt == 2){
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-4, COLS/2-3, "Create GAME");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(95));
                mvprintw(LINES/2-2, COLS/2-3, "Load GAME");
                attroff(COLOR_PAIR(95));
                attron(COLOR_PAIR(85));
                mvprintw(LINES/2, COLS/2-3, "Back");
                attroff(COLOR_PAIR(85));
            }
        }
    }
    attroff(A_BOLD);
    return cnt;
}