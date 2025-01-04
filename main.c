// IN THE NAME OF GOD!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include<time.h>
#include "menu.c"
//#define KEY_ENTER 10
#define N 1000
int FLOOR;
typedef struct Position{
    int x, y;
} Position;
typedef struct Player
{
    Position position;
    int health;
    
} Player;
typedef struct Room{
    Position position;
    int height, width;
    int *enemy;
    Position *door;
    int doornum;
    int *gold;
    int *spell;
    int *guns;
} Room;
char map[4][200][200];
int Create_room(int level, Room *room);
int Create_map();
void player_move(Player* User, int x, int y, int input);
void input_player(Player *User, int x);
bool check_print(int x, int y){
    return (map[FLOOR][x][y] != '#' && map[FLOOR][x][y] != ' ' && mvinch(x, y) != map[FLOOR][x][y]);
}
void BFS(int x, int y){
    mvprintw(x, y, "%c", map[FLOOR][x][y]);
    if(check_print(x-1, y)){
        BFS(x-1, y);
    }
    if(check_print(x+1, y)){
        BFS(x+1, y);
    }
    if(check_print(x, y+1)){
        BFS(x, y+1);
    }
    if(check_print(x, y-1)){
        BFS(x, y-1);
    }
    
}
void copy_map(int level){
    for(int i = 0; i < LINES; i++){
        for(int j = 0; j < COLS;j++){
            map[level][i][j] = mvinch(i, j);
        }
    }
}
int draw_line(int level, Position A, Position B){
    if(map[level][A.x+1][A.y] == ' '){
        A.x++;
    }
    else if(map[level][A.x-1][A.y] == ' '){
        A.x--;
    }
    else if(map[level][A.x][A.y-1] == ' '){
        A.y--;
    }
    else{
        A.y++;
    }
    if(map[level][B.x+1][B.y] == ' '){
        B.x++;
    }
    else if(map[level][B.x-1][B.y] == ' '){
        B.x--;
    }
    else if(map[level][B.x][B.y-1] == ' '){
        B.y--;
    }
    else{
        B.y++;
    }
    //mvprintw(A.x, A.y, "#");
    //mvprintw(B.x, B.y, "#");
    map[level][A.x][A.y] = '#';
    map[level][B.x][B.y] = '#';
    Position tmp;
    tmp.x = A.x, tmp.y = A.y;
    while(1){
        int cntt = 0;
        // left
        if(abs((tmp.x-1)-B.x) < abs(tmp.x-B.x) && map[level][tmp.x-1][tmp.y] == ' '){
            //mvprintw(tmp.x-1, tmp.y, "#");
            tmp.x--;
            map[level][tmp.x][tmp.y] = '#';
        }
        // right
        else if(abs((tmp.x+1)-B.x) < abs(tmp.x-B.x) && map[level][tmp.x+1][tmp.y] == ' '){
            //mvprintw(tmp.x+1, tmp.y, "#");
            tmp.x++;
            map[level][tmp.x][tmp.y] = '#';
        }
        // up
        else if(abs((tmp.y-1)-B.y) < abs(tmp.y-B.y) && map[level][tmp.x][tmp.y-1] == ' '){
            //mvprintw(tmp.x, tmp.y-1, "#");
            tmp.y--;
            map[level][tmp.x][tmp.y] = '#';
        }
        // down
        else if(abs((tmp.y+1)-B.y) < abs(tmp.y-B.y) && map[level][tmp.x][tmp.y+1] == ' '){
            //mvprintw(tmp.x, tmp.y+1, "#");
            tmp.y++;
            map[level][tmp.x][tmp.y] = '#';
        }
        else{
            break;
        }
    }
}
int Create_room(int level, Room *room){
    // mvprintw(2, 1, "%d", (room->position).x);
    for(int i = room->position.y; i <= room->position.y+room->width; i++){
        //mvprintw(room->position.x, i, "-");
        //mvprintw(room->position.x+room->height, i, "-");
        map[level][room->position.x][i] = '-';
        map[level][room->position.x+room->height][i] = '-';
    }
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        // mvprintw(i, room->position.y, "|");
        // mvprintw(i, room->position.y+room->width, "|");
        map[level][i][room->position.y] = '|';
        map[level][i][room->position.y+room->width] = '|';
    }
    //attron(COLOR_PAIR(111));
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        for(int j = room->position.y+1; j < room->position.y+room->width; j++){
            //mvprintw(i, j, ".");
            map[level][i][j] = '.';
        }
    }
    //attroff(COLOR_PAIR(111));
    for(int i = 0; i < room->doornum; i++){
        //mvprintw(room->door[i].x, room->door[i].y, "+");
        map[level][room->door[i].x][room->door[i].y] = '+';
    }
    return 1;
}
int Create_map(int level){
    Room *room[6];
    for(int i = 0; i < 6; i++){
        room[i] = malloc(sizeof(Room));
    }
    // room[0]
    room[0]->doornum = 2;
    room[0]->position.x = rand()%10+1, room[0]->position.y = rand()%20+1;
    room[0]->door = malloc(sizeof(Position) * 2), room[0]->width = rand()%8+12, room[0]->height=rand()%5+8;
    room[0]->door[0].x = room[0]->position.x+room[0]->height, room[0]->door[0].y = room[0]->position.y + rand()%(room[0]->width-2)+1;
    room[0]->door[1].x = room[0]->position.x+1+rand()%(room[0]->height-2), room[0]->door[1].y = room[0]->position.y+room[0]->width;
    // room[1]
    room[1]->doornum = 2;
    room[1]->position.x = rand()%10+1+25, room[1]->position.y = rand()%20+1;
    room[1]->door = malloc(sizeof(Position) * 2), room[1]->width = rand()%8+12, room[1]->height=rand()%5+8;
    room[1]->door[0].x = room[1]->position.x, room[1]->door[0].y = room[1]->position.y + rand()%(room[1]->width-2)+1;
    room[1]->door[1].x = room[1]->position.x+1+rand()%(room[1]->height-2), room[1]->door[1].y = room[1]->position.y+room[1]->width;
    //room[2]
    room[2]->doornum = 3;
    room[2]->position.x = rand()%10+1, room[2]->position.y = rand()%20+60+1;
    room[2]->door = malloc(sizeof(Position) * 3), room[2]->width = rand()%8+12, room[2]->height=rand()%5+8;
    room[2]->door[0].x = room[2]->position.x+room[2]->height, room[2]->door[0].y = room[2]->position.y + rand()%(room[2]->width-2)+1;
    room[2]->door[1].x = room[2]->position.x+1+rand()%(room[2]->height-2), room[2]->door[1].y = room[2]->position.y+room[2]->width;
    room[2]->door[2].x = room[2]->position.x+1+rand()%(room[2]->height-2), room[2]->door[2].y = room[2]->position.y;
    //room[3]
    room[3]->doornum = 3;
    room[3]->position.x = rand()%10+1+25, room[3]->position.y = rand()%20+60+1;
    room[3]->door = malloc(sizeof(Position) * 3), room[3]->width = rand()%8+12, room[3]->height=rand()%5+8;
    room[3]->door[0].x = room[3]->position.x, room[3]->door[0].y = room[3]->position.y + rand()%(room[3]->width-2)+1;
    room[3]->door[1].x = room[3]->position.x+1+rand()%(room[3]->height-2), room[3]->door[1].y = room[3]->position.y+room[3]->width;
    room[3]->door[2].x = room[3]->position.x+1+rand()%(room[3]->height-2), room[3]->door[2].y = room[3]->position.y;
    //room[4]
    room[4]->doornum = 2;
    room[4]->position.x = rand()%10+1, room[4]->position.y = rand()%20+120+1;
    room[4]->door = malloc(sizeof(Position) * 2), room[4]->width = rand()%8+12, room[4]->height=rand()%5+8;
    room[4]->door[0].x = room[4]->position.x+room[4]->height, room[4]->door[0].y = room[4]->position.y + rand()%(room[4]->width-2)+1;
    room[4]->door[1].x = room[4]->position.x+1+rand()%(room[4]->height-2), room[4]->door[1].y = room[4]->position.y;
    //room[5]
    room[5]->doornum = 2;
    room[5]->position.x = rand()%10+1+25, room[5]->position.y = rand()%20+120+1;
    room[5]->door = malloc(sizeof(Position) * 2), room[5]->width = rand()%8+12, room[5]->height=rand()%5+8;
    room[5]->door[0].x = room[5]->position.x, room[5]->door[0].y = room[5]->position.y + rand()%(room[5]->width-2)+1;
    room[5]->door[1].x = room[5]->position.x+1+rand()%(room[5]->height-2), room[5]->door[1].y = room[5]->position.y;
    for(int i = 0; i < 6; i++){
        Create_room(level,room[i]);
    }
    draw_line(level,room[0]->door[0], room[1]->door[0]);
    draw_line(level,room[0]->door[1], room[2]->door[2]);
    draw_line(level,room[1]->door[1], room[3]->door[2]);
    draw_line(level,room[2]->door[0], room[3]->door[0]);
    draw_line(level,room[2]->door[1], room[4]->door[1]);
    draw_line(level,room[5]->door[0], room[4]->door[0]);
    draw_line(level,room[5]->door[1], room[3]->door[1]);
    return 1;
}
void update_map(Player *User, int input){
    switch(map[FLOOR][User->position.x][User->position.y]){
        case '#':
            if(input == KEY_DOWN){
                for(int i = 4; i >= 1; i--){
                    if(map[FLOOR][User->position.x+i][User->position.y] == '#' && mvinch(User->position.x+i,User->position.y) != 28467){
                        mvprintw(User->position.x+i,User->position.y,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_UP){
                for(int i = 4; i >= 1; i--){
                    if(map[FLOOR][User->position.x-i][User->position.y] == '#' && mvinch(User->position.x-i,User->position.y) != 28467){
                        mvprintw(User->position.x-i,User->position.y,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_LEFT){
                for(int i = 4; i >= 1; i--){
                    if(map[FLOOR][User->position.x][User->position.y-i] == '#' && mvinch(User->position.x,User->position.y-i) != 28467){
                        mvprintw(User->position.x,User->position.y-i,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_RIGHT){
                for(int i = 4; i >= 1; i--){
                    if(map[FLOOR][User->position.x][User->position.y+i] == '#' && mvinch(User->position.x,User->position.y+i) != 28467){
                        mvprintw(User->position.x,User->position.y+i,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else{

            }
            break;
        case '+' :
        case '.' :
            BFS(User->position.x,User->position.y);
            break;
    }
}
void player_move(Player* User, int x, int y, int input){
    switch (map[FLOOR][x][y])
    {
    case '.':
    case 28462:
    case '+':
    case '#':
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(111));
        mvprintw(User->position.x, User->position.y,"%c", map[FLOOR][User->position.x][User->position.y]);
        attroff(COLOR_PAIR(111));
        User->position.x = x;
        User->position.y = y;
        update_map(User, input);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(110));
        printw("@");
        attroff(COLOR_PAIR(110));
        move(User->position.x, User->position.y);
        break;
    default:
        mvprintw(1, 1, "%d", mvinch(x, y));
        break;
    }
}
void input_player(Player *User, int x){
    switch (x){
        case KEY_UP:
            player_move(User, User->position.x-1, User->position.y, x);
            break;
        case KEY_DOWN:
            player_move(User, User->position.x+1, User->position.y, x);
            break;
        case KEY_LEFT:
            player_move(User, User->position.x, User->position.y-1, x);
            break;
        case KEY_RIGHT:
            player_move(User, User->position.x, User->position.y+1, x);
            break;
        default:
            break;
    }
}
Player * init_player(){
    int x, y;
    for(int i = 1; i < 20; i++){
        for(int j = 1;j < 20;j++){
            if(map[FLOOR][i][j] == '.'){
                x = i, y = j;
                break;
            }
        }
    }
    Player *user = malloc(sizeof(Player));
    user->position.x = x, user->position.y = y;
    return user;
}
int main(){
    FLOOR = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 200; j++)
            for(int k = 0; k < 200; k++)
                map[i][j][k] = ' ';
    initscr();
    start_color();
    init_pair(110, COLOR_RED, COLOR_BLACK);
    init_pair(111, COLOR_GREEN, COLOR_BLACK);
    srand(time(NULL));
    curs_set(0);
    keypad(stdscr, TRUE);
    //menu_user();
    Create_map(0);
    // copy_map(0);
    Player *User = init_player();
    mvprintw(User->position.x, User->position.y, "@");
    move(User->position.x, User->position.y);
    
    update_map(User, 0);
    while(1){
        int x = getch();
        if(x == 'q'){
            for(int i = 0; i < COLS-1; i++){
                for(int j = 0; j < LINES-1; j++){
                    mvprintw(j, i, "%c", map[0][j][i]);
                }
            }
        }
        input_player(User, x);
        // mvprintw(User->position.x, User->position.y, "@");
        // move(User->position.x, User->position.y);
    }
    refresh();
    endwin();
}
