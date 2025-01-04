// IN THE NAME OF GOD!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include<time.h>
#include "connect.c"
#include "music.c"
//#define KEY_ENTER 10
#define N 1000
char user_name[N], user_email[N], user_pass[N];
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
    start_color();
    attron(A_BOLD);
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Enter your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2-2, COLS/2-3, "%s", user_name);
        attroff(COLOR_PAIR(100));
        if(is_new(user_name)){
            break;
        }
    }
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        attron(A_BOLD);
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvprintw(LINES/2-2, COLS/2-3, "%s", user_name);
        attroff(COLOR_PAIR(100));
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-1, COLS/2-3, "Enter your email:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2, COLS/2-3, "%s", user_email);
        attroff(COLOR_PAIR(100));
        if(is_valid_email(user_email)){
            attron(COLOR_PAIR(101));
            attron(A_BOLD);
            mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
            mvprintw(LINES/2-3, COLS/2-3, "Your name:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "%s", user_name);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-1, COLS/2-3, "Your email:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "%s", user_email);
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
            attron(A_BOLD);
            mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
            mvprintw(LINES/2-3, COLS/2-3, "Your name:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2-2, COLS/2-3, "%s", user_name);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-1, COLS/2-3, "Your email:");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES/2, COLS/2-3, "%s", user_email);
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2+1, COLS/2-3, "Enter your password (it must contain a-z and A-z and 0-9):");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvscanw(LINES/2+2, COLS/2-3, "%s", user_pass);
            attroff(COLOR_PAIR(100));
            if(is_valid_pass(user_pass)){
                break;
            }
        }
    }
    else{
        char *newpass = random_pass();
        for(int i = 0; i < strlen(newpass); i++){
            user_pass[i] = newpass[i];
        }
    }
    Create_user(user_name, user_email, user_pass);
    clear();
    attron(COLOR_PAIR(101));
    attron(A_BOLD);
    mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
    mvprintw(LINES/2-3, COLS/2-3, "Your name:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2, COLS/2-3, "%s", user_name);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2-1, COLS/2-3, "Your email:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2, COLS/2-3, "%s", user_email);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(101));
    mvprintw(LINES/2+1, COLS/2-3, "Your pass:");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2+2, COLS/2-3, "%s", user_pass);
    attroff(COLOR_PAIR(100));
    attron(COLOR_PAIR(104));
    mvprintw(1, COLS/2-3, "%s", "Press any KEY to go back to menu!");
    attroff(COLOR_PAIR(104));
    int yy = getch();
    clear();
    menu_user();
}
void login_user(){
    start_color();
    attron(A_BOLD);
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Enter your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2-2, COLS/2-3, "%s", user_name);
        attroff(COLOR_PAIR(100));
        if(!is_new(user_name)){
            break;
        }
    }
    while(1){
        clear();
        attron(COLOR_PAIR(101));
        attron(A_BOLD);
        mvprintw(LINES/2-4, COLS/2-3, "WELCOME TO MY GAME!");
        mvprintw(LINES/2-3, COLS/2-3, "Your name:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvprintw(LINES/2-2, COLS/2-3, "%s", user_name);
        attroff(COLOR_PAIR(100));
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-1, COLS/2-3, "Enter your password:");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvscanw(LINES/2, COLS/2-3, "%s", user_pass);
        attroff(COLOR_PAIR(100));
        if(is_ok(user_name, user_pass)){
            break;
        }
    }
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
    mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
            mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
                mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
                mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
                mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
                mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
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
                mvprintw(LINES/2+2, COLS/2-3, "MUSIC");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2+4, COLS/2-3, "GUEST");
                attroff(COLOR_PAIR(101));
            }
        }
    }
    if(!cnt){
        create_user();
    }
    else if(cnt == 1){
        login_user();
    }
    else if(cnt == 3){
        clear();
        attron(COLOR_PAIR(101));
        mvprintw(LINES/2-2, COLS/2-3, "ON");
        attroff(COLOR_PAIR(101));
        attron(COLOR_PAIR(100));
        mvprintw(LINES/2, COLS/2-3, "OFF");
        attroff(COLOR_PAIR(100));
        int cnt2 = 0;
        while(1){
            int xy = getch();
            clear();
            if((xy == KEY_DOWN && cnt2 == 0)){
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2-2, COLS/2-3, "ON");
                attroff(COLOR_PAIR(100));
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2, COLS/2-3, "OFF");
                attroff(COLOR_PAIR(101));
                cnt2 = 1;
            }
            else if((xy == KEY_UP && cnt2 == 1)){
                attron(COLOR_PAIR(101));
                mvprintw(LINES/2-2, COLS/2-3, "ON");
                attroff(COLOR_PAIR(101));
                attron(COLOR_PAIR(100));
                mvprintw(LINES/2, COLS/2-3, "OFF");
                attroff(COLOR_PAIR(100));
                cnt2 = 0;
            }
            else if(xy == 10){
                break;
            }
            else{
                if(cnt2 == 0){
                    attron(COLOR_PAIR(101));
                    mvprintw(LINES/2-2, COLS/2-3, "ON");
                    attroff(COLOR_PAIR(101));
                    attron(COLOR_PAIR(100));
                    mvprintw(LINES/2, COLS/2-3, "OFF");
                    attroff(COLOR_PAIR(100));
                }
                else{
                    attron(COLOR_PAIR(100));
                    mvprintw(LINES/2-2, COLS/2-3, "ON");
                    attroff(COLOR_PAIR(100));
                    attron(COLOR_PAIR(101));
                    mvprintw(LINES/2-0, COLS/2-3, "OFF");
                    attroff(COLOR_PAIR(101));
                }
            }
        }
        if(cnt2 == 0){
            music_on();
        }
        else{
            music_off();
        }
        menu_user();
    }
}


