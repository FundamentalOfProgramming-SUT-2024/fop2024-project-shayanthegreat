// IN THE NAME OF GOD!
#include "main.h"
#include "menu.h"
#include "scoreboard.h"
#include "monster.h"
#include "music.h"
#include<wchar.h>
// Room* rooms[4][6];
// tile map[4][200][200];W
Level levels[5];
int FLOOR = 0, HEALTH = 0, MAX_HEALTH = 0, HUNGER = 0, MAX_HUNGER = 0;
int CHAMP_COLOR, LAST_MOVE;
long long TIME_START;
int GLOBAL_INCREMENT_DAMAGE;
int GLOBAL_INCREMENT_SPEED;
int MUSIC_STATUS;
bool FLAG;
bool PARCHAM;
struct timespec ts;
Userinfo *userinfo;
Player *User;
bool timer[1000000];
int getroom(Position position){
    if(levels[FLOOR].map[position.x][position.y].type == -1 || levels[FLOOR].map[position.x][position.y].type == -3){
        return -1;
    }
    int res = 0;
    if(position.y < 60){
        res = 0;
    }
    else if(position.y < 120){
        res = 1;
    }
    else{
        res = 2;
    }
    res *= 2;
    if(position.x > 25){
        res++; 
    }
    return res;
}
void stair_handle(int cnt){
    if(FLOOR + cnt >= 4 || FLOOR + cnt < 0){
        return ;
    }
    levels[FLOOR].copy_map = copy_line(LINES);
    FLOOR += cnt;
    User->position.x = levels[FLOOR].stair.x;
    User->position.y = levels[FLOOR].stair.y;
    clear();
    refresh();
    if(levels[FLOOR].copy_map==NULL){
        update_map(User, 0);
    }
    else{
        print_line(LINES, levels[FLOOR].copy_map);
    }
    refresh();
    attron(COLOR_PAIR(CHAMP_COLOR));
    mvprintw(User->position.x, User->position.y, "@");
    attroff(COLOR_PAIR(CHAMP_COLOR));
    refresh();
    move(User->position.x, User->position.y);
}
bool check_cor(int x, int y){
    if(x < 0 || y < 0 || x >= LINES || y >= COLS){
        return 0;
    }
    return levels[FLOOR].map[x][y].symbol == '#' && mvinch(x,y) != 28467;
}
void EatFood(food food){
    switch(food.type){
        case 0:
            User->health+=40;
            User->hunger++;
            break;
        case -1:
            User->health-=5;
            break;
        case 1:
            User->health+=20;
            GLOBAL_INCREMENT_DAMAGE = 15;
            break;
        case 2:
            User->health+=20;
            GLOBAL_INCREMENT_SPEED = 15;
            break;
        default:
            break;
    }
}
bool check_print(int x, int y){
    if(x < 0 || y < 0){
        return 0;
    }
    if(x >= LINES || y >= COLS){
        return 0;
    }
    if(levels[FLOOR].map[x][y].visit){
        return 0;
    }
    return (levels[FLOOR].map[x][y].type != -5 && levels[FLOOR].map[x][y].type != -1 && mvinch(x, y) != levels[FLOOR].map[x][y].symbol && levels[FLOOR].map[x][y].type != -6);
}
bool empty(int x, int y){
    if(levels[FLOOR].map[x][y].type == -7){
        return 0;
    }
    return !(levels[FLOOR].map[x][y].type >= 1 && levels[FLOOR].map[x][y].type <= 4);
}
void replace(int x, int y){
    levels[FLOOR].map[x][y].type = 0;
    levels[FLOOR].map[x][y].symbol = '.';
}
void update_gold(gold gold, Player *User){
    User->gold += gold.amount;
    char str[50] = "Added Gold : ";
    sprintf(str + strlen(str), "%d", gold.amount);
    message(str, 3);
}
void update_spell(spell spell, Player *User){
    User->spell[spell.type]++;
    switch(spell.type){
        case 0:
            message("A speed spell added", 4);
            break;
        case 1:
            message("A health spell added", 4);
            break;
        case 2:
            message("A damage spell added", 4);
            break;
    }
}
void update_food(food foodi, Player *User){
    if(User->fooditem == 5){
        message("Sorry Sir your Bag is Full!", 1);
        return;
    }
    foodi.time = time(0);
    User->food[User->fooditem++] = foodi;
    message("A Food was added!", 2);
}
void update_gun(gun GUN, Player *User){
    // mvprintw(1, 1, "yes");
    switch(GUN.type){
        case 1:
            User->gunnumber[1] += 10;
            break;
        case 2:
            User->gunnumber[2] += 8;
            break;
        case 3:
            User->gunnumber[3] += 5;
            break;
        case 4:
            User->gunnumber[4] += 1000000;
        default :
            break;
    }
    message("A Gun was added!", 3);
}
void BFS(int x, int y){
    if(!check_print(x, y))
        return ;
    levels[FLOOR].map[x][y].visit=1;
    if(levels[FLOOR].map[x][y].type == 0 || levels[FLOOR].map[x][y].type == -3 || levels[FLOOR].map[x][y].type == -2 || levels[FLOOR].map[x][y].type == -7 || levels[FLOOR].map[x][y].type == -8)
        mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
    else if(levels[FLOOR].map[x][y].type == 1){
        switch(levels[FLOOR].map[x][y].symbol){
            case 'a':
            case 'd':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🍎");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
            break;
            case 'b':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🔋");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
            break;
            case 'c':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🏎️");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
            break;
        }
    }
    else if(levels[FLOOR].map[x][y].type == 2){
        levels[FLOOR].map[x][y-1].type = -6;
        switch(levels[FLOOR].map[x][y].symbol){
            case 'M':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🔨");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'D':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🪓");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'W':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🪄");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'A':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🏹");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'S':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🗡️");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
        }
    }
    else if(levels[FLOOR].map[x][y].type == 3){
        levels[FLOOR].map[x][y-1].type = -6;
        switch(levels[FLOOR].map[x][y].symbol){
            case 'z':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🪙");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'x':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "💰");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
            break;
        }
    }
    else if(levels[FLOOR].map[x][y].type == 4){
        levels[FLOOR].map[x][y-1].type = -6;
        switch(levels[FLOOR].map[x][y].symbol){
            case 'a':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "🚀");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'b':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "💊");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
            case 'c':
            if(empty(x, y-1)){
                levels[FLOOR].map[x][y-1].type = -6;
                levels[FLOOR].map[x][y-1].visit=1;
                mvprintw(x, y-1, "💪");
            }
            else{
                replace(x, y);
                mvprintw(x, y, "%c", levels[FLOOR].map[x][y].symbol);
            }
                break;
        }
    }
    if(check_print(x, y-1)){
        BFS(x, y-1);
    }
    if(check_print(x, y+1)){
        BFS(x, y+1);
    }
    if(check_print(x-1, y)){
        BFS(x-1, y);
    }
    if(check_print(x+1, y)){
        BFS(x+1, y);
    }
}
int draw_line(int level, Position A, Position B){
    if(levels[level].map[A.x+1][A.y].symbol == ' '){
        A.x++;
    }
    else if(levels[level].map[A.x-1][A.y].symbol == ' '){
        A.x--;
    }
    else if(levels[level].map[A.x][A.y-1].symbol == ' '){
        A.y--;
    }
    else{
        A.y++;
    }
    if(levels[level].map[B.x+1][B.y].symbol == ' '){
        B.x++;
    }
    else if(levels[level].map[B.x-1][B.y].symbol == ' '){
        B.x--;
    }
    else if(levels[level].map[B.x][B.y-1].symbol == ' '){
        B.y--;
    }
    else{
        B.y++;
    }
    //mvprintw(A.x, A.y, "#");
    //mvprintw(B.x, B.y, "#");
    levels[level].map[A.x][A.y].symbol = '#';
    levels[level].map[B.x][B.y].symbol = '#';
    levels[level].map[A.x][A.y].type = -1;
    levels[level].map[B.x][B.y].type = -1;
    Position tmp;
    tmp.x = A.x, tmp.y = A.y;
    for(int i = 0; i < 5000; i++){
        // left
        if(abs((tmp.x-1)-B.x) < abs(tmp.x-B.x) && levels[level].map[tmp.x-1][tmp.y].symbol == ' ' && rand()%2){
            //mvprintw(tmp.x-1, tmp.y, "#");
            tmp.x--;
            levels[level].map[tmp.x][tmp.y].symbol = '#';
            levels[level].map[tmp.x][tmp.y].type = -1;
        }
        // right
        else if(abs((tmp.x+1)-B.x) < abs(tmp.x-B.x) && levels[level].map[tmp.x+1][tmp.y].symbol == ' ' && rand()%2){
            //mvprintw(tmp.x+1, tmp.y, "#");
            tmp.x++;
            levels[level].map[tmp.x][tmp.y].symbol = '#';

            levels[level].map[tmp.x][tmp.y].type = -1;
        }
        // up
        else if(abs((tmp.y-1)-B.y) < abs(tmp.y-B.y) && levels[level].map[tmp.x][tmp.y-1].symbol == ' ' && rand()%2){
            //mvprintw(tmp.x, tmp.y-1, "#");
            tmp.y--;
            levels[level].map[tmp.x][tmp.y].symbol = '#';

            levels[level].map[tmp.x][tmp.y].type = -1;
        }
        // down
        else if(abs((tmp.y+1)-B.y) < abs(tmp.y-B.y) && levels[level].map[tmp.x][tmp.y+1].symbol == ' ' && rand()%2){
            //mvprintw(tmp.x, tmp.y+1, "#");
            tmp.y++;
            levels[level].map[tmp.x][tmp.y].symbol = '#';

            levels[level].map[tmp.x][tmp.y].type = -1;
        }
    }
}
int Create_stair(int level){
    int x, y;
    int cnt = 0;
    int num = rand()%6;
    x  = levels[level].rooms[num]->position.x+1+rand()%(levels[level].rooms[num]->height-2);
    y  = levels[level].rooms[num]->position.y+1+rand()%(levels[level].rooms[num]->width-2);
    while(levels[level].map[x][y].type != 0 || levels[level].map[x][y+1].type == 1  || levels[level].map[x][y+1].type == 2 || levels[level].map[x][y+1].type == 3  || levels[level].map[x][y+1].type == 4){
        num = rand()%6;
        x  = levels[level].rooms[num]->position.x+1+rand()%(levels[level].rooms[num]->height-2);
        y  = levels[level].rooms[num]->position.y+1+rand()%(levels[level].rooms[num]->width-2);
        cnt++;
    }
    levels[level].map[x][y].symbol = '<';
    levels[level].map[x][y].type = -7;
    levels[level].stair.x = x, levels[level].stair.y = y;
}
int Create_room(int level, Room *room, int number){
    // mvprintw(2, 1, "%d", (room->position).x);
    for(int i = room->position.y; i <= room->position.y+room->width; i++){
        //mvprintw(room->position.x, i, "-");
        //mvprintw(room->position.x+room->height, i, "-");
        levels[level].map[room->position.x][i].symbol = '-';
        levels[level].map[room->position.x+room->height][i].symbol = '-';
        levels[level].map[room->position.x][i].type = -2;
        levels[level].map[room->position.x+room->height][i].type = -2;
    }
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        // mvprintw(i, room->position.y, "|");
        // mvprintw(i, room->position.y+room->width, "|");
        levels[level].map[i][room->position.y].symbol = '|';
        levels[level].map[i][room->position.y+room->width].symbol = '|';
        levels[level].map[i][room->position.y].type = -2;
        levels[level].map[i][room->position.y+room->width].type = -2;

    }
    //attron(COLOR_PAIR(111));
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        for(int j = room->position.y+1; j < room->position.y+room->width; j++){
            //mvprintw(i, j, ".");
            levels[level].map[i][j].symbol = '.';
            levels[level].map[i][j].type = 0;
        }
    }
    // adding food
    int count = 1 + rand()%2;
    room->foodnum = count;
    room->food = malloc(count * sizeof(food));
    for(int i = 0; i  < count ; i++){
        room->food[i].y = room->position.y+2+rand()%(room->width-3);
        room->food[i].x = room->position.x+2+rand()%(room->height-3);
        while(levels[level].map[room->food[i].x][room->food[i].y].type != 0){  
            room->food[i].y = room->position.y+2+rand()%(room->width-3);
            room->food[i].x = room->position.x+2+rand()%(room->height-3);
        }
        room->food[i].type = (rand()%4)-1;
        if(room->food[i].type<0){
            room->food[i].type = (rand()%2)-1;
        }
        levels[level].map[room->food[i].x][room->food[i].y].DET.x = number;
        levels[level].map[room->food[i].x][room->food[i].y].DET.y = i;
        // rand()%4; 
        levels[level].map[room->food[i].x][room->food[i].y].type = 1;
        switch(room->food[i].type){
            case 0:
                levels[level].map[room->food[i].x][room->food[i].y].symbol = 'a';
                break;
            case -1:
                levels[level].map[room->food[i].x][room->food[i].y].symbol = 'd';
                break;
            case 1:
                levels[level].map[room->food[i].x][room->food[i].y].symbol = 'b';
                break;
            case 2:
                levels[level].map[room->food[i].x][room->food[i].y].symbol = 'c';
                break;
        }
    }
    // adding gun
    count = rand()%3;
    room->gunnum = count;
    room->gun = malloc(count * sizeof(gun));
    for(int i = 0; i  < count; i++){
        room->gun[i].y = room->position.y+2+rand()%(room->width-3);
        room->gun[i].x = room->position.x+2+rand()%(room->height-3);
        while(levels[level].map[room->gun[i].x][room->gun[i].y].type != 0){  
            room->gun[i].y = room->position.y+2+rand()%(room->width-3);
            room->gun[i].x = room->position.x+2+rand()%(room->height-3);
        }
        room->gun[i].type = rand()%4+1;
        levels[level].map[room->gun[i].x][room->gun[i].y].DET.x = number;
        levels[level].map[room->gun[i].x][room->gun[i].y].DET.y = i;
        // rand()%4; 
        levels[level].map[room->gun[i].x][room->gun[i].y].type = 2;
        switch(room->gun[i].type){
            case 0:
                room->gun[i].damage = 5;
                levels[level].map[room->gun[i].x][room->gun[i].y].symbol = 'M';
                break;
            case 1:
                room->gun[i].damage = 12;
                levels[level].map[room->gun[i].x][room->gun[i].y].symbol = 'D';
                break;
            case 2:
                room->gun[i].damage = 15;
                levels[level].map[room->gun[i].x][room->gun[i].y].symbol = 'W';
                break;
            case 3:
                room->gun[i].damage = 5;
                levels[level].map[room->gun[i].x][room->gun[i].y].symbol = 'A';
                break;
            case 4:
                room->gun[i].damage = 10;
                levels[level].map[room->gun[i].x][room->gun[i].y].symbol = 'S';
                break;
        }
    }
    // add gold
    count = rand()%3;
    room->golditem = count;
    room->gold = malloc(count * sizeof(gold));
    for(int i = 0; i  < count; i++){
        room->gold[i].y = room->position.y+2+rand()%(room->width-3);
        room->gold[i].x = room->position.x+2+rand()%(room->height-3);
        while(levels[level].map[room->gold[i].x][room->gold[i].y].type != 0){  
            room->gold[i].y = room->position.y+2+rand()%(room->width-3);
            room->gold[i].x = room->position.x+2+rand()%(room->height-3);
        }
        room->gold[i].type = (rand()%6 == 0);
        levels[level].map[room->gold[i].x][room->gold[i].y].DET.x = number;
        levels[level].map[room->gold[i].x][room->gold[i].y].DET.y = i;
        levels[level].map[room->gold[i].x][room->gold[i].y].type = 3;
        switch(room->gold[i].type){
            case 0:
                room->gold[i].amount = rand()%5+10;
                levels[level].map[room->gold[i].x][room->gold[i].y].symbol = 'z';
                break;
            case 1:
                room->gold[i].amount = rand()%50+100;
                levels[level].map[room->gold[i].x][room->gold[i].y].symbol = 'x';
                break;
        }
    }
    // add spell
    count = rand()%3;
    room->spellitem = count;
    room->spell = malloc(count * sizeof(spell));
    for(int i = 0; i  < count; i++){
        room->spell[i].y = room->position.y+2+rand()%(room->width-3);
        room->spell[i].x = room->position.x+2+rand()%(room->height-3);
        while(levels[level].map[room->spell[i].x][room->spell[i].y].type != 0){  
            room->spell[i].y = room->position.y+2+rand()%(room->width-3);
            room->spell[i].x = room->position.x+2+rand()%(room->height-3);
        }
        room->spell[i].type = rand()%3;
        levels[level].map[room->spell[i].x][room->spell[i].y].DET.x = number;
        levels[level].map[room->spell[i].x][room->spell[i].y].DET.y = i;
        levels[level].map[room->spell[i].x][room->spell[i].y].type = 4;
        switch(room->spell[i].type){
            case 0:
                levels[level].map[room->spell[i].x][room->spell[i].y].symbol = 'a';
                break;
            case 1:
                levels[level].map[room->spell[i].x][room->spell[i].y].symbol = 'b';
                break;
            case 2:
                levels[level].map[room->spell[i].x][room->spell[i].y].symbol = 'c';
                break;
        }
    }
    //attroff(COLOR_PAIR(111));
    for(int i = 0; i < room->doornum; i++){
        //mvprintw(room->door[i].x, room->door[i].y, "+");
        levels[level].map[room->door[i].x][room->door[i].y].symbol = '+';
        levels[level].map[room->door[i].x][room->door[i].y].type = -3;
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
    room[0]->position.x = rand()%10+2, room[0]->position.y = rand()%20+1;
    room[0]->door = malloc(sizeof(Position) * 2), room[0]->width = rand()%8+14, room[0]->height=rand()%5+8;
    room[0]->door[0].x = room[0]->position.x+room[0]->height, room[0]->door[0].y = room[0]->position.y + rand()%(room[0]->width-2)+1;
    room[0]->door[1].x = room[0]->position.x+1+rand()%(room[0]->height-2), room[0]->door[1].y = room[0]->position.y+room[0]->width;
    // room[1]
    room[1]->doornum = 2;
    room[1]->position.x = rand()%10+1+25, room[1]->position.y = rand()%20+1;
    room[1]->door = malloc(sizeof(Position) * 2), room[1]->width = rand()%8+14, room[1]->height=rand()%5+8;
    room[1]->door[0].x = room[1]->position.x, room[1]->door[0].y = room[1]->position.y + rand()%(room[1]->width-2)+1;
    room[1]->door[1].x = room[1]->position.x+1+rand()%(room[1]->height-2), room[1]->door[1].y = room[1]->position.y+room[1]->width;
    //room[2]
    room[2]->doornum = 3;
    room[2]->position.x = rand()%10+2, room[2]->position.y = rand()%20+60+1;
    room[2]->door = malloc(sizeof(Position) * 3), room[2]->width = rand()%8+14, room[2]->height=rand()%5+8;
    room[2]->door[0].x = room[2]->position.x+room[2]->height, room[2]->door[0].y = room[2]->position.y + rand()%(room[2]->width-2)+1;
    room[2]->door[1].x = room[2]->position.x+1+rand()%(room[2]->height-2), room[2]->door[1].y = room[2]->position.y+room[2]->width;
    room[2]->door[2].x = room[2]->position.x+1+rand()%(room[2]->height-2), room[2]->door[2].y = room[2]->position.y;
    //room[3]
    room[3]->doornum = 3;
    room[3]->position.x = rand()%10+1+25, room[3]->position.y = rand()%20+60+1;
    room[3]->door = malloc(sizeof(Position) * 3), room[3]->width = rand()%8+14, room[3]->height=rand()%5+8;
    room[3]->door[0].x = room[3]->position.x, room[3]->door[0].y = room[3]->position.y + rand()%(room[3]->width-2)+1;
    room[3]->door[1].x = room[3]->position.x+1+rand()%(room[3]->height-2), room[3]->door[1].y = room[3]->position.y+room[3]->width;
    room[3]->door[2].x = room[3]->position.x+1+rand()%(room[3]->height-2), room[3]->door[2].y = room[3]->position.y;
    //room[4]
    room[4]->doornum = 2;
    room[4]->position.x = rand()%10+2, room[4]->position.y = rand()%20+120+1;
    room[4]->door = malloc(sizeof(Position) * 2), room[4]->width = rand()%8+14, room[4]->height=rand()%5+8;
    room[4]->door[0].x = room[4]->position.x+room[4]->height, room[4]->door[0].y = room[4]->position.y + rand()%(room[4]->width-2)+1;
    room[4]->door[1].x = room[4]->position.x+1+rand()%(room[4]->height-2), room[4]->door[1].y = room[4]->position.y;
    //room[5]
    room[5]->doornum = 2;
    room[5]->position.x = rand()%10+1+25, room[5]->position.y = rand()%20+120+1;
    room[5]->door = malloc(sizeof(Position) * 2), room[5]->width = rand()%8+14, room[5]->height=rand()%5+8;
    room[5]->door[0].x = room[5]->position.x, room[5]->door[0].y = room[5]->position.y + rand()%(room[5]->width-2)+1;
    room[5]->door[1].x = room[5]->position.x+1+rand()%(room[5]->height-2), room[5]->door[1].y = room[5]->position.y;
    for(int i = 0; i < 6; i++){
        Create_room(level,room[i], i);
        levels[level].rooms[i] = room[i];
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
    switch(levels[FLOOR].map[User->position.x][User->position.y].type){
        case -1:
            levels[FLOOR].map[User->position.x][User->position.y].visit = 1;
            if(input == KEY_DOWN){
                for(int i = 1; i <= 4; i++){
                    if(check_cor(User->position.x+i,User->position.y)){
                        levels[FLOOR].map[User->position.x+i][User->position.y].visit = 1;
                        mvprintw(User->position.x+i,User->position.y,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_UP){
                for(int i = 1; i <= 4; i++){
                    if(check_cor(User->position.x-i,User->position.y)){
                        levels[FLOOR].map[User->position.x-i][User->position.y].visit = 1;
                        mvprintw(User->position.x-i,User->position.y,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_LEFT){
                for(int i = 1; i <= 4; i++){
                    if(check_cor(User->position.x,User->position.y-i)){
                        levels[FLOOR].map[User->position.x][User->position.y-i].visit = 1;
                        mvprintw(User->position.x,User->position.y-i,"#");
                    }
                    else{
                        break;
                    }
                }
            }
            else if(input == KEY_RIGHT){
                for(int i = 1; i <= 4; i++){
                    if(check_cor(User->position.x,User->position.y+i)){
                        levels[FLOOR].map[User->position.x][User->position.y+i].visit = 1;
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
        case 0:
            BFS(User->position.x,User->position.y);
            break;
        case -3 :
            BFS(User->position.x,User->position.y);
            break;
        case -7 :
            BFS(User->position.x,User->position.y);
            break;
        case 1:
            update_food(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->food[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
            break;
        case 2:
            update_gun(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gun[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
            break;
        case 3:
            update_gold(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gold[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
            break;
        default :
            break;
    }
}

void player_move(Player* User, int x, int y, int input){
    switch (levels[FLOOR].map[x][y].type)
    {
    case 0:
        move(User->position.x, User->position.y);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        update_map(User, input);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        break;
    case -1:
    case -3:
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(111));
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        attroff(COLOR_PAIR(111));
        User->position.x = x;
        User->position.y = y;
        update_map(User, input);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        break;
    case 1:
        move(User->position.x, User->position.y);
        levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
        mvprintw(x, y, ".");
        if(levels[FLOOR].map[x][y-1].type != -7){
            levels[FLOOR].map[x][y-1].type = 0, levels[FLOOR].map[x][y-1].symbol = '.';
        }
        mvprintw(x, y-1, "%c", levels[FLOOR].map[x][y-1].symbol);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        update_food(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->food[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
        break;
    case 2:
        move(User->position.x, User->position.y);
        levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
        mvprintw(x, y, ".");
        if(levels[FLOOR].map[x][y-1].type != -7){
            levels[FLOOR].map[x][y-1].type = 0, levels[FLOOR].map[x][y-1].symbol = '.';
        }
        mvprintw(x, y-1, "%c", levels[FLOOR].map[x][y-1].symbol);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        update_gun(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gun[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
        break;
    case 3:
        move(User->position.x, User->position.y);
        levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
        mvprintw(x, y, ".");
        if(levels[FLOOR].map[x][y-1].type != -7){
            levels[FLOOR].map[x][y-1].type = 0, levels[FLOOR].map[x][y-1].symbol = '.';
        }
        mvprintw(x, y-1, "%c", levels[FLOOR].map[x][y-1].symbol);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        update_gold(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gold[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
        break;   
    case 4:
        move(User->position.x, User->position.y);
        levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
        mvprintw(x, y, ".");
        if(levels[FLOOR].map[x][y-1].type != -7){
            levels[FLOOR].map[x][y-1].type = 0, levels[FLOOR].map[x][y-1].symbol = '.';
        }
        mvprintw(x, y-1, "%c", levels[FLOOR].map[x][y-1].symbol);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        update_spell(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->spell[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
        break;  
    case -6:
        mvprintw(User->position.x, User->position.y, ".");
        switch (levels[FLOOR].map[x][y+1].type){
            case 1:
                levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
                mvprintw(x, y, ".");
                levels[FLOOR].map[x][y+1].type = 0, levels[FLOOR].map[x][y+1].symbol = '.';
                User->position.x = x, User->position.y = y+1;
                move(User->position.x, User->position.y);
                attron(COLOR_PAIR(CHAMP_COLOR));
                printw("@");
                attroff(COLOR_PAIR(CHAMP_COLOR));
                move(User->position.x, User->position.y);
                update_food(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->food[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
                break;
            case 2:
                levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
                mvprintw(x, y, ".");
                levels[FLOOR].map[x][y+1].type = 0, levels[FLOOR].map[x][y+1].symbol = '.';
                User->position.x = x, User->position.y = y+1;
                move(User->position.x, User->position.y);
                attron(COLOR_PAIR(CHAMP_COLOR));
                printw("@");
                attroff(COLOR_PAIR(CHAMP_COLOR));
                move(User->position.x, User->position.y);
                update_gun(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gun[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
                break;
            case 3:
                levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
                mvprintw(x, y, ".");
                levels[FLOOR].map[x][y+1].type = 0, levels[FLOOR].map[x][y+1].symbol = '.';
                User->position.x = x, User->position.y = y+1;
                move(User->position.x, User->position.y);
                attron(COLOR_PAIR(CHAMP_COLOR));
                printw("@");
                attroff(COLOR_PAIR(CHAMP_COLOR));
                move(User->position.x, User->position.y);
                update_gold(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->gold[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
                break;
            case 4:
                levels[FLOOR].map[x][y].type = 0, levels[FLOOR].map[x][y].symbol = '.';
                mvprintw(x, y, ".");
                levels[FLOOR].map[x][y+1].type = 0, levels[FLOOR].map[x][y+1].symbol = '.';
                User->position.x = x, User->position.y = y+1;
                move(User->position.x, User->position.y);
                attron(COLOR_PAIR(CHAMP_COLOR));
                printw("@");
                attroff(COLOR_PAIR(CHAMP_COLOR));
                move(User->position.x, User->position.y);
                update_spell(levels[FLOOR].rooms[levels[FLOOR].map[User->position.x][User->position.y].DET.x]->spell[levels[FLOOR].map[User->position.x][User->position.y].DET.y], User);
                break;
        }
        break;
    case -7:
        move(User->position.x, User->position.y);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        update_map(User, input);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        break;
    case -8:
        // WHAT TO DO IN MARG ROOM
        FLAG = 1;
        break;
    case 5:
        move(User->position.x, User->position.y);
        mvprintw(User->position.x, User->position.y,"%c", levels[FLOOR].map[User->position.x][User->position.y].symbol);
        User->position.x = x;
        User->position.y = y;
        switch(levels[FLOOR].map[x][y].symbol){
            case '$':
                User->gunnumber[1]++;
                break;
            case '&':
                User->gunnumber[2]++;
                break;
            case '*':
                User->gunnumber[3]++;
                break;    
        }
        levels[FLOOR].map[x][y].symbol = '.';
        levels[FLOOR].map[x][y].type = 0;
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y); 
        break;
    default:
        mvprintw(1, 1, "%d", levels[FLOOR].map[x][y].type);
        break;
    }
}
void input_player(Player *User, int x){
    switch (x){
        case KEY_UP:
            player_move(User, User->position.x-1, User->position.y, x);
            if(User->activespell[0] || GLOBAL_INCREMENT_SPEED >= 1){
                player_move(User, User->position.x-1, User->position.y, x);
            }
            for(int i = 0; i < 3; i++){
                User->activespell[i] = max(User->activespell[i]-1, 0);
            }
            break;
        case KEY_DOWN:
            player_move(User, User->position.x+1, User->position.y, x);
            if(User->activespell[0] || GLOBAL_INCREMENT_SPEED >= 1){
                player_move(User, User->position.x+1, User->position.y, x);
            }
            for(int i = 0; i < 3; i++){
                User->activespell[i] = max(User->activespell[i]-1, 0);
            }
            break;
        case KEY_LEFT:
            player_move(User, User->position.x, User->position.y-1, x);
            if(User->activespell[0] || GLOBAL_INCREMENT_SPEED >= 1){
                player_move(User, User->position.x, User->position.y-1, x);
            }
            for(int i = 0; i < 3; i++){
                User->activespell[i] = max(User->activespell[i]-1, 0);
            }
            break;
        case KEY_RIGHT:
            player_move(User, User->position.x, User->position.y+1, x);
            if(User->activespell[0] || GLOBAL_INCREMENT_SPEED >= 1){
                player_move(User, User->position.x, User->position.y+1, x);
            }
            for(int i = 0; i < 3; i++){
                User->activespell[i] = max(User->activespell[i]-1, 0);
            }
            break;
        case 'e':
            move(User->position.x, User->position.y);
            attron(COLOR_PAIR(CHAMP_COLOR));
            printw("@");
            attroff(COLOR_PAIR(CHAMP_COLOR));
            move(User->position.x, User->position.y);
            Show_food(User->food, User->fooditem);
            break;
        case 'z':
            move(User->position.x, User->position.y);
            attron(COLOR_PAIR(CHAMP_COLOR));
            printw("@");
            attroff(COLOR_PAIR(CHAMP_COLOR));
            move(User->position.x, User->position.y);
            Show_spell();
            break;
        case 'i':
            move(User->position.x, User->position.y);
            attron(COLOR_PAIR(CHAMP_COLOR));
            printw("@");
            attroff(COLOR_PAIR(CHAMP_COLOR));
            move(User->position.x, User->position.y);
            Show_gun();
            break;
        case 44:
            if(levels[FLOOR].map[User->position.x][User->position.y].type == -7){
                stair_handle(+1);
            }
            break;
        case 46:
            if(levels[FLOOR].map[User->position.x][User->position.y].type == -7){
                stair_handle(-1);
            }
            break;
        case 32:
            switch(User->activegun){
                case 0:
                case 4:
                attack(FLOOR, -1);
                break;
                case 1:
                case 2:
                case 3:
                int xy = getch();
                LAST_MOVE = xy;
                attack(FLOOR, xy);
                break;
            }
        break;
        case 'a':
            switch(LAST_MOVE){
                case KEY_DOWN:
                case KEY_UP:
                case KEY_LEFT:
                case KEY_RIGHT:
                    if(User->activegun >= 1 && User->activegun <= 3){
                        attack(FLOOR, LAST_MOVE);
                    }
                    break;
                default:
                    break;
            }
        break;
        default:
            break;
    }
}
Player * init_player(){
    int x, y;
    int num = rand() % 6;
    x  = levels[FLOOR].rooms[num]->position.x+1+rand()%(levels[FLOOR].rooms[num]->height-2);
    y  = levels[FLOOR].rooms[num]->position.y+1+rand()%(levels[FLOOR].rooms[num]->width-2);
    while(levels[FLOOR].map[x][y].type != 0){
        num = rand()%6;
        x  = levels[FLOOR].rooms[num]->position.x+1+rand()%(levels[FLOOR].rooms[num]->height-2);
        y  = levels[FLOOR].rooms[num]->position.y+1+rand()%(levels[FLOOR].rooms[num]->width-2);
    }
    Player *user = malloc(sizeof(Player));
    user->position.x = x, user->position.y = y;
    user->fooditem=0, user->gold=0;
    // TODO
    //user->gunitem = 0;
    for(int i = 0; i < 5; i++){
        user->gunnumber[i] = 0;
    }
    user->gunnumber[0] = 100000000;
    user->activegun = 0;
    user->spell[0] = 0, user->spell[1] = 0, user->spell[2] = 0;
    user->health = HEALTH, user->hunger = HUNGER;
    for(int i = 0; i < 3; i++)
        user->activespell[i] = 0;
    return user;
}
void message(char *msg, int color){
    int x, y;
    getyx(stdscr, x, y);
    move(1, 0);
    clrtoeol();
    attron(COLOR_PAIR(color) | A_BOLD | A_ITALIC);
    mvprintw(1, 3, "%s", msg);
    attroff(COLOR_PAIR(color) | A_BOLD | A_ITALIC);
    refresh();
    TIME_START++;
    napms(400);
    move(1, 0);
    clrtoeol();
    move(x, y);
}
void message2(char *msg, int color, int longer){
    int x, y;
    getyx(stdscr, x, y);
    move(1, 0);
    clrtoeol();
    attron(COLOR_PAIR(color) | A_BOLD | A_ITALIC);
    mvprintw(1, COLS/2-3, "%s", msg);
    attroff(COLOR_PAIR(color) | A_BOLD | A_ITALIC);
    refresh();
}
WINDOW *Create_window(int width, int height){
    int start_y = 0;
    int start_x = 0;
    WINDOW *popup_win = newwin(height, width, start_y, start_x);
    return popup_win;
}
wchar_t **copy_line(int n) {
    wchar_t **line = (wchar_t **)malloc(n * sizeof(wchar_t *));
    for (int i = 0; i < n; i++) {
        line[i] = (wchar_t *)malloc(COLS * sizeof(wchar_t));
        for (int j = 0; j < COLS; j++) {
            line[i][j] = mvinch(i, j);
        }
    }
    return line;
}
void print_line(int n, wchar_t **line){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < COLS; j++){
            if(levels[FLOOR].map[i][j].visit){
                if(levels[FLOOR].map[i][j].type == 1){
                    levels[FLOOR].map[i][j-1].type = -6;
                    switch(levels[FLOOR].map[i][j].symbol){
                        case 'a':
                        case 'd':
                        mvprintw(i, j-1, "🍎");
                            break;
                        case 'b':
                        mvprintw(i, j-1, "🔋");
                            break;
                        case 'c':
                        mvprintw(i, j-1, "🏎️");
                            break;
                    }
                }
                else if(levels[FLOOR].map[i][j].type == 2){
                    levels[FLOOR].map[i][j-1].type = -6;
                    switch(levels[FLOOR].map[i][j].symbol){
                        case 'M':
                        mvprintw(i, j-1, "🔨");
                            break;
                        case 'D':
                        mvprintw(i, j-1, "🪓");
                            break;
                        case 'W':
                        mvprintw(i, j-1, "🪄");
                            break;
                        case 'A':
                        mvprintw(i, j-1, "🏹");
                            break;
                        case 'S':
                        mvprintw(i, j-1, "🗡️");
                            break;
                    }
                }
                else if(levels[FLOOR].map[i][j].type == 3){
                    levels[FLOOR].map[i][j-1].type = -6;
                    switch(levels[FLOOR].map[i][j].symbol){
                        case 'z':
                        mvprintw(i, j-1, "🪙");
                            break;
                        case 'x':
                        mvprintw(i, j-1, "💰");
                            break;
                    }
                }
                else if(levels[FLOOR].map[i][j].type == 4){
                    levels[FLOOR].map[i][j-1].type = -6;
                    switch(levels[FLOOR].map[i][j].symbol){
                        case 'a':
                        mvprintw(i, j-1, "🚀");
                            break;
                        case 'b':
                        mvprintw(i, j-1, "💊");
                            break;
                        case 'c':
                        mvprintw(i, j-1, "💪");
                            break;
                    }
                }
                else if(levels[FLOOR].map[i][j].type == 0 || levels[FLOOR].map[i][j].type == -3 || levels[FLOOR].map[i][j].type == -2 || levels[FLOOR].map[i][j].type == -1 || levels[FLOOR].map[i][j].type == -7 || levels[FLOOR].map[i][j].type == -8){
                    mvaddch(i, j, line[i][j]);
                }
            }
            else{
                mvaddch(i, j, ' ');
            }
        }
    }
}
void Show_food(food* food, int count){
    wchar_t** line = copy_line(10);
    WINDOW* popup_win = Create_window(COLS, 10);
    wrefresh(popup_win);
    wattron(popup_win, COLOR_PAIR(2) | A_BOLD | A_ITALIC);
    move(1, 1);
    wprintw(popup_win, "Your bag : (choose a number from 1 to %d or press any random key to leave the menu!)\n", count);
    for(int i = 0 ;i < count; i++){
        char type[50];
        int noww = time(0);
        int xyxyxy = noww - food[i].time;
        if(xyxyxy >= 20){
            food[i].time = time(0);
            food[i].type = max(-1, food[i].type-1);
        }
        switch(food[i].type){
            case 0:
            case -1:
                wprintw(popup_win, "Apple\n");
                break;
            case 1:
                wprintw(popup_win, "Power Poition\n");
                break;
            case 2:
                wprintw(popup_win, "Speed Poition\n");
                break;
        }
    }
    wattroff(popup_win, COLOR_PAIR(3) | A_BOLD | A_ITALIC);
    int x = wgetch(popup_win)-'0';
    if(x >= 1 && x <= count){
        EatFood(food[x-1]);
        for(int i = x; i < count; i++){
            food[i-1] = food[i];
        }
        User->fooditem--;
    }
    wrefresh(popup_win);
    delwin(popup_win);
    print_line(10, line);
    refresh();
    return;
}
void Show_gun(){
    wchar_t** line = copy_line(10);
    WINDOW* popup_win = Create_window(COLS, 10);
    wrefresh(popup_win);
    wattron(popup_win, COLOR_PAIR(3) | A_BOLD | A_ITALIC);
    move(1, 1);
    wprintw(popup_win, "Press ESE to exit : \n");

    wprintw(popup_win, "Your bag : \n");
    switch (User->activegun){
        case 0:
            wprintw(popup_win, "Active Gun : Mace \n");
            break;
        case 1:
            wprintw(popup_win, "Active Gun : Dagger \n");
            break;
        case 2:
            wprintw(popup_win, "Active Gun : Magic Wand \n");
            break;
        case 3:
            wprintw(popup_win, "Active Gun : Normal arrow \n");
            break;
        case 4:
            wprintw(popup_win, "Active Gun : Sword \n");
            break;
        default:
            wprintw(popup_win, "Active Gun : Nothing \n");
            break;
    }
    wprintw(popup_win, "Short Range : \n");
    wprintw(popup_win, "A Mace with: %d damage!  (' w ') \n", 5);
    wprintw(popup_win, "%d Sword with: %d damage!  (' t ') \n", (User->gunnumber[4] > 0) ,10);
    wprintw(popup_win, "Long Range : \n");
    wprintw(popup_win, "%d Dagger with: %d demage!  (' y ') \n",User->gunnumber[1], 12);
    wprintw(popup_win, "%d Magic Wand with: %d damage!  (' u ') \n",User->gunnumber[2], 15);
    wprintw(popup_win, "%d Normal arrow with: %d damage!  (' r ') \n",User->gunnumber[3], 5);
    wattroff(popup_win, COLOR_PAIR(3) | A_BOLD | A_ITALIC);
    wrefresh(popup_win);
    while(1){
        int x = wgetch(popup_win);
        if(x == 27){
            break;
        }
        switch (x){
            case 'w':
                if(User->activegun == 0){
                    User->activegun = -1;
                    message("Unloaded Successfully!", 2);
                }
                else if(User->activegun == -1){
                    User->activegun = 0;
                    message("Active Gun changed to Mace!", 2);
                }
                else{
                    message("First Unload your previous Gun!", 1);
                }
                break;
            case 't':
                if(User->activegun == 4){
                    User->activegun = -1;
                    message("Unloaded Successfully!", 2);
                }
                else if(User->activegun == -1){
                    User->activegun = 4;
                    message("Active Gun changed to Sword!", 2);
                }
                else{
                    message("First Unload your previous Gun!", 1);
                }
                break;
            case 'y':
                if(User->activegun == 1){
                    User->activegun = -1;
                    message("Unloaded Successfully!", 2);
                }
                else if(User->activegun == -1){
                    User->activegun = 1;
                    message("Active Gun changed to Dagger!", 2);
                }
                else{
                    message("First Unload your previous Gun!", 1);
                }
                break;
            case 'u':
                if(User->activegun == 2){
                    User->activegun = -1;
                    message("Unloaded Successfully!", 2);
                }
                else if(User->activegun == -1){
                    User->activegun = 2;
                    message("Active Gun changed to Magic Wand!", 2);
                }
                else{
                    message("First Unload your previous Gun!", 1);
                }
                break;
            case 'r':
                if(User->activegun == 3){
                    User->activegun = -1;
                    message("Unloaded Successfully!", 2);
                }
                else if(User->activegun == -1){
                    User->activegun = 3;
                    message("Active Gun changed to Normal arrow!", 2);
                }
                else{
                    message("First Unload your previous Gun!", 1);
                }
                break;
        }
    }
    delwin(popup_win);
    print_line(10, line);
    refresh();
    return;
}
void Show_spell(){
    wchar_t** line = copy_line(10);
    WINDOW* popup_win = Create_window(COLS, 10);
    wrefresh(popup_win);
    wattron(popup_win, COLOR_PAIR(4) | A_BOLD | A_ITALIC);
    move(1, 1);
    wprintw(popup_win, "Your spells (choose any that you 1-3 or press a random key!): \n");
    wprintw(popup_win, "Speed spells : %d\n", User->spell[0]);
    wprintw(popup_win, "Health spells : %d\n", User->spell[1]);
    wprintw(popup_win, "Damage spells : %d\n", User->spell[2]);
    wattroff(popup_win, COLOR_PAIR(3) | A_BOLD | A_ITALIC);
    wrefresh(popup_win);
    int x = wgetch(popup_win)-'0';
    if(x >= 1 && x <= 3){
        if(User->spell[x-1] > 0){
            User->spell[x-1]--;
            User->activespell[x-1] += 10;
        }
    }
    delwin(popup_win);
    print_line(10, line);
    refresh();
    return;
}
int min(int x, int y){
    if(x <= y)
        return x;
    return y;
}
int max(int x, int y){
    if(x >= y){
        return x;
    }
    return y;
}
void display_health(){
    clock_gettime(0, &ts);
    long long TIME_NOW = (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    long long xxx = TIME_NOW - TIME_START;
    xxx /= 1000000;
    xxx += 1;
    User->hunger = min(User->hunger, MAX_HUNGER);
    User->health = min(User->health, MAX_HEALTH);
    if(timer[xxx]){
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "HUNGER:");
        for(int i = 0; i < User->hunger; i++){
            mvprintw(0, i+8, "#");
        }
        for(int i = User->hunger; i < MAX_HUNGER; i++){
            mvprintw(0, i+8, "-");
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
        mvprintw(0, 70, "HEALTH:");
        for(int i = 0; i < User->health; i++){
            mvprintw(0, i+80, "#");
        }
        for(int i = User->health; i < MAX_HEALTH; i++){
            mvprintw(0, i+80, "-");
        }
        attroff(COLOR_PAIR(2));
        return ; 
    }
    GLOBAL_INCREMENT_DAMAGE--, GLOBAL_INCREMENT_SPEED--;
    timer[xxx] = 1;
    if(xxx % 40 == 0 && User->hunger > 0){
        User->hunger = max(0, User->hunger-1);   
    }
    if((User->hunger == 0 || User->hunger > MAX_HUNGER) && (xxx % 6 == 0)){
        User->health--;
    }
    else if(User->hunger == MAX_HUNGER && (xxx % 3 == 0)){
        User->health = min(User->health+(1+(User->activespell[1]>0)), MAX_HEALTH);
    }
    if(User->health <= 0){
        PARCHAM = 1;
        return ;
    }
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "HUNGER:");
    for(int i = 0; i < User->hunger; i++){
        mvprintw(0, i+8, "#");
    }
    for(int i = User->hunger; i < MAX_HUNGER; i++){
        mvprintw(0, i+8, "-");
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(0, 70, "HEALTH:");
    for(int i = 0; i < User->health; i++){
        mvprintw(0, i+80, "#");
    }
    for(int i = User->health; i < MAX_HEALTH; i++){
        mvprintw(0, i+80, "-");
    }
    attroff(COLOR_PAIR(2));
}
void SAVE_ME(const char *filename) {
        // TODO SAVE TO USERS SPECIAL FILE
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for saving");
        return;
    }
    fwrite(&FLOOR, sizeof(int), 1, file);
    fwrite(&MAX_HEALTH, sizeof(int), 1, file);
    fwrite(&MAX_HUNGER, sizeof(int), 1, file);
    fwrite(&HUNGER, sizeof(int), 1, file);
    fwrite(&CHAMP_COLOR, sizeof(int), 1, file);
    fwrite(&GLOBAL_INCREMENT_DAMAGE, sizeof(int), 1, file);
    fwrite(&GLOBAL_INCREMENT_SPEED, sizeof(int), 1, file);
    MUSIC_STATUS = music_status;
    fwrite(&MUSIC_STATUS, sizeof(int), 1, file);
    Player NEWUSER;
    for(int i = 0; i < 3; i++){
        NEWUSER.activespell[i] = User->activespell[i];
        NEWUSER.spell[i] = User->spell[i];
    }
    for(int i = 0; i < User->fooditem; i++){
        NEWUSER.food[i] = User->food[i];
    }
    for(int i = 0; i < 5; i++){
        NEWUSER.gunnumber[i] = User->gunnumber[i];
    }
    NEWUSER.gold = User->gold;
    NEWUSER.health = User->health;
    NEWUSER.hunger = User->hunger;
    NEWUSER.position = User->position;
    NEWUSER.activegun = User->activegun;
    NEWUSER.fooditem = User->fooditem;
    NEWUSER.point = User->point;
    fwrite(&NEWUSER, sizeof(Player), 1, file);
    fclose(file);
    //printf("Data saved successfully to %s\n", filename);
}
void LOAD_ME(const char *filename) {
        // TODO LOAD FROM USERS SPECIAL FILE
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for loading");
        return;
    }

    fread(&FLOOR, sizeof(int), 1, file);
    fread(&MAX_HEALTH, sizeof(int), 1, file);
    fread(&MAX_HUNGER, sizeof(int), 1, file);
    fread(&HUNGER, sizeof(int), 1, file);
    fread(&CHAMP_COLOR, sizeof(int), 1, file);
    fread(&GLOBAL_INCREMENT_DAMAGE, sizeof(int), 1, file);
    fread(&GLOBAL_INCREMENT_SPEED, sizeof(int), 1, file);
    fread(&MUSIC_STATUS, sizeof(int), 1, file);
    Player NEWUSER;
    fread(&NEWUSER, sizeof(Player), 1, file);
    for(int i = 0; i < 3; i++){
        User->activespell[i] = NEWUSER.activespell[i];
        User->spell[i] = NEWUSER.spell[i];
    }
    for(int i = 0; i < User->fooditem; i++){
        User->food[i] = NEWUSER.food[i];
    }
    for(int i = 0; i < 5; i++){
        User->gunnumber[i] = NEWUSER.gunnumber[i];
    }
    User->gold = NEWUSER.gold;
    User->health = NEWUSER.health;
    User->hunger = NEWUSER.hunger; 
    User->position = NEWUSER.position;
    User->activegun = NEWUSER.activegun;
    User->fooditem = NEWUSER.fooditem;
    User->point = NEWUSER.point;
    fclose(file);
    //printf("Data loaded successfully from %s\n", filename);
}
void save_level(FILE *file, Level *level) {
    // Write rooms
    for (int i = 0; i < 6; i++) {
        Room *room = level->rooms[i];
        if (room != NULL) {
            fwrite(room, sizeof(Room), 1, file);

            // Write food in the room
            fwrite(&room->foodnum, sizeof(int), 1, file);
            if (room->foodnum > 0) {
                fwrite(room->food, sizeof(food), room->foodnum, file);
            }

            // Write guns in the room
            fwrite(&room->gunnum, sizeof(int), 1, file);
            if (room->gunnum > 0) {
                fwrite(room->gun, sizeof(gun), room->gunnum, file);
            }

            // Write gold in the room
            fwrite(&room->golditem, sizeof(int), 1, file);
            if (room->golditem > 0) {
                fwrite(room->gold, sizeof(gold), room->golditem, file);
            }

            // Write spells in the room
            fwrite(&room->spellitem, sizeof(int), 1, file);
            if (room->spellitem > 0) {
                fwrite(room->spell, sizeof(spell), room->spellitem, file);
            }
        }
    }
    // Write the tile map
    fwrite(level->map, sizeof(tile), 200 * 200, file);

    // Write the stair position
    fwrite(&level->stair, sizeof(Position), 1, file);

    // Write copy_map
    // Write copy_map with NULL checks
    int rows = 0, cols = 0;
    if (level->copy_map != NULL) {
        // Calculate the number of rows (LINES) in copy_map
        rows = LINES, cols = COLS;

        // Write the number of rows (LINES) and columns (COLS)
        fwrite(&rows, sizeof(int), 1, file);
        fwrite(&cols, sizeof(int), 1, file);

        // Write each row of the copy_map (ensure valid rows)
        for (int i = 0; i < rows; i++) {
            if (level->copy_map[i] != NULL) {
                fwrite(level->copy_map[i], sizeof(wchar_t), cols, file);
            }
        }
    } 
    else {
        // If copy_map is NULL, write 0 for rows and cols to indicate the absence
        rows = 0;
        cols = 0;
        fwrite(&rows, sizeof(int), 1, file);  // Write 0 for rows
        fwrite(&cols, sizeof(int), 1, file);  // Write 0 for cols
    }


    // Write monsters
    fwrite(&level->monstersnum, sizeof(int), 1, file);
    for (int i = 0; i < level->monstersnum; i++) {
        fwrite(level->monsters[i], sizeof(Monster), 1, file);
    }
}
void save_all_levels(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open file for saving\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        save_level(file, &levels[i]);
    }

    fclose(file);
}
void load_level(FILE *file, Level *level) {
    // Read rooms
    for (int i = 0; i < 6; i++) {
        Room *room = malloc(sizeof(Room));
        if (fread(room, sizeof(Room), 1, file) == 1) {
            level->rooms[i] = room;

            // Read food in the room
            fread(&room->foodnum, sizeof(int), 1, file);
            if (room->foodnum > 0) {
                room->food = malloc(sizeof(food) * room->foodnum);
                fread(room->food, sizeof(food), room->foodnum, file);
            } else {
                room->food = NULL;
            }

            // Read guns in the room
            fread(&room->gunnum, sizeof(int), 1, file);
            if (room->gunnum > 0) {
                room->gun = malloc(sizeof(gun) * room->gunnum);
                fread(room->gun, sizeof(gun), room->gunnum, file);
            } else {
                room->gun = NULL;
            }

            // Read gold in the room
            fread(&room->golditem, sizeof(int), 1, file);
            if (room->golditem > 0) {
                room->gold = malloc(sizeof(gold) * room->golditem);
                fread(room->gold, sizeof(gold), room->golditem, file);
            } else {
                room->gold = NULL;
            }

            // Read spells in the room
            fread(&room->spellitem, sizeof(int), 1, file);
            if (room->spellitem > 0) {
                room->spell = malloc(sizeof(spell) * room->spellitem);
                fread(room->spell, sizeof(spell), room->spellitem, file);
            } else {
                room->spell = NULL;
            }
        } else {
            free(room);
            level->rooms[i] = NULL;
        }
    }

    // Read the tile map
    fread(level->map, sizeof(tile), 200 * 200, file);

    // Read the stair position
    fread(&level->stair, sizeof(Position), 1, file);

    // Read copy_map
    int rows = 0, cols = 0;
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);

    if (rows > 0 && cols > 0) {
        level->copy_map = malloc(sizeof(wchar_t *) * rows);
        for (int i = 0; i < rows; i++) {
            level->copy_map[i] = malloc(sizeof(wchar_t) * (cols + 1));
            fread(level->copy_map[i], sizeof(wchar_t), cols, file);
            level->copy_map[i][cols] = L'\0'; // Null-terminate each row
        }
    } else {
        level->copy_map = NULL;
    }

    // Read monsters
    fread(&level->monstersnum, sizeof(int), 1, file);
    for (int i = 0; i < level->monstersnum; i++) {
        level->monsters[i] = malloc(sizeof(Monster));
        fread(level->monsters[i], sizeof(Monster), 1, file);
    }
}
void load_all_levels(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file for loading\n");
        return;
    }
    for (int i = 0; i < 4; i++) {
        load_level(file, &levels[i]);
    }
    fclose(file);
}
void LOAD_GAME(){
    User = malloc(sizeof(Player ));
    // TODO LOAD FROM USERS SPECIAL FILE
    char sttttr[50] = "user/";
    strcat(sttttr,userinfo->user_name);
    strcat(sttttr,"/bins.bin");
    load_all_levels(sttttr);
    strcpy(sttttr, "user/");
    strcat(sttttr,userinfo->user_name);
    strcat(sttttr,"/bins2.bin");
    LOAD_ME(sttttr);
    music_on(MUSIC_STATUS);
    print_line(LINES, levels[FLOOR].copy_map);
}
void CREATE_GAME(){
    HUNGER = 30;
    if(HEALTH == 0){
        HEALTH = 70;
    }
    for(int i = 0 ; i < 4; i++){
        Create_map(i);
        Create_stair(i);
        Create_level_monster(i);
    }
    create_X();
    User = init_player();
}

int Create_room_marg(int level, Room *room){
    for(int i = room->position.y; i <= room->position.y+room->width; i++){
        levels[level].map[room->position.x][i].symbol = '-';
        levels[level].map[room->position.x+room->height][i].symbol = '-';
        levels[level].map[room->position.x][i].type = -2;
        levels[level].map[room->position.x+room->height][i].type = -2;
    }
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        levels[level].map[i][room->position.y].symbol = '|';
        levels[level].map[i][room->position.y+room->width].symbol = '|';
        levels[level].map[i][room->position.y].type = -2;
        levels[level].map[i][room->position.y+room->width].type = -2;

    }
    for(int i = room->position.x+1; i < room->position.x+room->height; i++){
        for(int j = room->position.y+1; j < room->position.y+room->width; j++){
            levels[level].map[i][j].symbol = '.';
            levels[level].map[i][j].type = 0;
        }
    }
    int count = rand()%10+20;
    room->golditem = count;
    room->gold = malloc(count * sizeof(gold));
    for(int i = 0; i  < count; i++){
        room->gold[i].y = room->position.y+2+rand()%(room->width-3);
        room->gold[i].x = room->position.x+2+rand()%(room->height-3);
        while(levels[level].map[room->gold[i].x][room->gold[i].y].type != 0){  
            room->gold[i].y = room->position.y+2+rand()%(room->width-3);
            room->gold[i].x = room->position.x+2+rand()%(room->height-3);
        }
        room->gold[i].type = (rand()%6 == 0);
        levels[level].map[room->gold[i].x][room->gold[i].y].DET.x = 0;
        levels[level].map[room->gold[i].x][room->gold[i].y].DET.y = i;
        levels[level].map[room->gold[i].x][room->gold[i].y].type = 3;
        switch(room->gold[i].type){
            case 0:
                room->gold[i].amount = rand()%50+100;
                levels[level].map[room->gold[i].x][room->gold[i].y].symbol = 'z';
                break;
            case 1:
                room->gold[i].amount = rand()%500+1000;
                levels[level].map[room->gold[i].x][room->gold[i].y].symbol = 'x';
                break;
        }
    }
    return 1;
}

void print_game_over(int y, int x) {
    const char *game_over[] = {
        " GGGGG   AAAAA  M     M  EEEEE  OOOOO  V   V  EEEEE  RRRRR  ",
        "G        A   A  MM   MM  E      O   O  V   V  E      R    R ",
        "G  GG    AAAAA  M M M M  EEEE   O   O  V   V  EEEE   RRRRR  ",
        "G   G    A   A  M  M  M  E      O   O   V V   E      R  R   ",
        " GGGG    A   A  M     M  EEEEE  OOOOO    V    EEEEE  R   R  "
    };

    attron(COLOR_PAIR(95));
    for (int i = 0; i < 5; i++) {
        mvprintw(y + i, x, game_over[i]);
    }
    attroff(COLOR_PAIR(95));

    mvprintw(LINES/2, COLS/2-15, "YOU GOT %-5d golds BUT still lost :)", User->gold);

}

void lose_function() {
    clear();
    cbreak();                 
    noecho();                 
    int height, width;
    getmaxyx(stdscr, height, width);

    int start_x = (width - 50) / 2;
    int start_y = height / 3;
    print_game_over(start_y, start_x);
    refresh();
}

void print_win_message(int y, int x) {
    const char *you_win[] = {
        " Y   Y   OOO   U   U     W   W  III  N   N  !!! ",
        "  Y Y   O   O  U   U     W   W   I   NN  N  !!! ",
        "   Y    O   O  U   U     W W W   I   N N N  !!! ",
        "   Y    O   O  U   U     W W W   I   N  NN      ",
        "   Y     OOO    UUU       W W   III  N   N  !!! "
    };

    attron(COLOR_PAIR(5));
    attron(A_BLINK);
    for (int i = 0; i < 5; i++) {
        mvprintw(y + i, x, you_win[i]);
    }
    attroff(COLOR_PAIR(5));
    attroff(A_BLINK);
}

void win_function() {    attroff(COLOR_PAIR(95) | A_BOLD);

    clear();
    cbreak();

    int height, width;
    getmaxyx(stdscr, height, width);

    int start_x = (width - 50) / 2;
    int start_y = height / 3;
    attron(COLOR_PAIR(3));  // Use yellow stars
    for (int i = 0; i < 150; i++) {
        int star_x = (rand() % (LINES-5)) + 2;
        int star_y = (rand() % (COLS-5)) + 2;
        mvprintw(star_x, star_y, "*");
    }
    attroff(COLOR_PAIR(3));
    print_win_message(start_y, start_x);
    mvprintw(LINES/2, COLS/2-20, "Dear %s: Congrats you Got : %d golds\n", userinfo->user_name, User->gold);
    
    refresh();
    Update_user(userinfo);
}

void print_save(int y, int x) {
    const char *saved[] = {
        "SSSSSS   AAAAA  V     V  EEEEE ",
        "S        A   A  V     V  E    ",
        "SSSSSS   AAAAA   V   V   EEEE ",
        "     S   A   A    V V    E       ",
        "SSSSSS   A   A     V     EEEEE  "
    };
          
    const char *he[] = {
    "H   H  EEEEE  IIIII   L             H   H  III  TTTTT  L       EEEEE  RRRRR",
    "H   H  E        I     L             H   H   I     T    L       E      R   R",
    "HHHHH  EEEE     I     L             HHHHH   I     T    L       EEEE   RRRRR",
    "H   H  E        I     L             H   H   I     T    L       E      R  R",
    "H   H  EEEEE  IIIII   LLLLL         H   H  III    T    LLLLL   EEEEE  R   R"
    };

    attron(COLOR_PAIR(2));
    for (int i = 0; i < 5; i++) {
        mvprintw(y + i, x, saved[i]);
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(95) | A_BOLD);
    for (int i = 0; i < 5; i++) {
        mvprintw(y+10 + i, x-15, he[i]);
    }
    attroff(COLOR_PAIR(95) | A_BOLD);
    refresh();
}

void save_function() {
    clear();
    cbreak();                 
    noecho();                 
    int height, width;
    getmaxyx(stdscr, height, width);

    int start_x = (width - 50) / 2;
    int start_y = height / 3;
    print_save(start_y, start_x);
    refresh();
}

void MARG_LEVEL(){
    clear();
    Room *room = malloc(sizeof(Room));
    room->position.x = rand()%10+5, room->position.y = rand()%10+20;
    room->height = rand()%5+30, room->width = rand()%10+90;
    Create_room_marg(4, room);
    levels[4].rooms[0] = room;
    int y = room->position.y+2+rand()%(room->width-3);
    int x = room->position.x+2+rand()%(room->height-3);
    while(levels[4].map[x][y].type != 0){
        y = room->position.y+2+rand()%(room->width-3);
        x = room->position.x+2+rand()%(room->height-3);
    }
    Create_level_monster_marg(4);
    FLOOR = 4;
    User->position.x = x, User->position.y = y;
    mvprintw(User->position.x, User->position.y, "@");
    move(User->position.x, User->position.y);
    update_map(User, 0);
    mvprintw(User->position.x, User->position.y, "@");
    move(User->position.x, User->position.y);
    move(User->position.x, User->position.y);
    attron(COLOR_PAIR(CHAMP_COLOR));
    printw("@");
    attroff(COLOR_PAIR(CHAMP_COLOR));
    move(User->position.x, User->position.y);
    while(1){
        noecho();
        timeout(1000);
        int x = getch();
        input_player(User, x);
        Update_level_monster_marg(4);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        display_health();
        if(PARCHAM){
            break;
        }
        bool FLAG2 = 0;
        for(int i = 0; i < levels[4].monstersnum; i++){
            if(levels[4].monsters[i]->type != -1){
                FLAG2 = 1;
            }
        }
        if(!FLAG2){
            break;
        }
    }
}

void create_X(){
    int level = 3;
    int x, y;
    int cnt = 0;
    int num = rand()%6;
    x  = levels[level].rooms[num]->position.x+1+rand()%(levels[level].rooms[num]->height-2);
    y  = levels[level].rooms[num]->position.y+1+rand()%(levels[level].rooms[num]->width-2);
    while(levels[level].map[x][y].type != 0 || levels[level].map[x][y+1].type == 1  || levels[level].map[x][y+1].type == 2 || levels[level].map[x][y+1].type == 3  || levels[level].map[x][y+1].type == 4){
        num = rand()%6;
        x  = levels[level].rooms[num]->position.x+1+rand()%(levels[level].rooms[num]->height-2);
        y  = levels[level].rooms[num]->position.y+1+rand()%(levels[level].rooms[num]->width-2);
        cnt++;
    }
    levels[level].map[x][y].symbol = 'X';
    levels[level].map[x][y].type = -8;
}



int main(){
    MAX_HUNGER = 30;
    MAX_HEALTH = 70;
    CHAMP_COLOR = 4;
    FLOOR = 0;
    userinfo = malloc(1 * sizeof(Userinfo));
    strcpy(userinfo->user_name, "guest");
    for(int i = 0; i <= 4; i++)
        for(int j = 0; j < 200; j++)
            for(int k = 0; k < 200; k++)
                levels[i].map[j][k].symbol = ' ', levels[i].map[j][k].type = -5, levels[i].map[j][k].visit = 0;
    for(int i = 0; i < 4; i++){
        levels[i].copy_map = NULL;
    }
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_color(COLOR_YELLOW, 1000, 800, 400);
    init_color(COLOR_ORANGE, 1000, 647, 0);
    init_color(COLOR_GOLD, 1000, 843, 0);
    init_color(COLOR_SILVER, 753, 753, 753);
    init_color(COLOR_BRONZE, 804, 498, 196);
    init_pair(110, COLOR_RED, COLOR_BLACK);
    init_pair(111, COLOR_GREEN, COLOR_BLACK);
    init_pair(95, COLOR_RED, COLOR_BLACK);
    init_pair(85,  COLOR_BLACK, COLOR_RED);
    init_pair(1,  COLOR_RED, COLOR_BLACK);
    init_pair(2,  COLOR_GREEN, COLOR_BLACK);
    init_pair(3,  COLOR_YELLOW, COLOR_BLACK);
    init_pair(4,  COLOR_ORANGE, COLOR_BLACK);
    init_pair(5,  COLOR_GOLD, COLOR_BLACK);
    init_pair(6,  COLOR_SILVER, COLOR_BLACK);
    init_pair(7,  COLOR_BRONZE, COLOR_BLACK);
    srand(time(NULL));
    curs_set(0);
    keypad(stdscr, TRUE);
    menu_user();
    int x = choose_mode();
    while(x == 2){
        menu_user();
        x = choose_mode();
    }
    if(x == 0){
        CREATE_GAME();
    }
    else{
        char sttttr[50] = "user/";
        strcat(sttttr,userinfo->user_name);
        strcat(sttttr,"/bins.bin");
        FILE *file = fopen(sttttr, "rb");
        if (!file) {
            message2("NO SAVED GAME !", 1, 1000);
            timeout(-1);
            getch();
            refresh();
            endwin();
            return 0;
        }
        else{
            fclose(file);
            LOAD_GAME();
        }
        
    }
    // STARTS GAME!

    
    clock_gettime(0, &ts);
    TIME_START = (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    mvprintw(User->position.x, User->position.y, "@");
    move(User->position.x, User->position.y);
    update_map(User, 0);
    mvprintw(User->position.x, User->position.y, "@");
    move(User->position.x, User->position.y);
    bool saved = 0;
    while(1){
        noecho();
        timeout(1000);
        int x = getch();
        input_player(User, x);
        if(FLAG){
            break;
        }
        Update_level_monster(FLOOR);
        move(User->position.x, User->position.y);
        attron(COLOR_PAIR(CHAMP_COLOR));
        printw("@");
        attroff(COLOR_PAIR(CHAMP_COLOR));
        move(User->position.x, User->position.y);
        display_health();
        if(PARCHAM){
            break;
        }
        if(x == 'b'){
            levels[FLOOR].copy_map = copy_line(LINES);
            char sttttr[50] = "user/";
            strcat(sttttr,userinfo->user_name);
            strcat(sttttr,"/bins.bin");
            save_all_levels(sttttr);
            strcpy(sttttr, "user/");
            strcat(sttttr,userinfo->user_name);
            strcat(sttttr,"/bins2.bin");
            SAVE_ME(sttttr);
            getch();
            saved = 1;
            break;
        }
    }
    if(saved == 1){
        save_function();
        timeout(-1);
        getch();
        endwin();
        return 0;
    }
    if(PARCHAM){
        lose_function();
        timeout(-1);
        getch();
        endwin();
        return 0;
    }
    MARG_LEVEL();
    if(PARCHAM){
        lose_function();
        timeout(-1);
        getch();
        endwin();
        return 0;
    }
    else{
        win_function();
        timeout(-1);
        getch();
        endwin();
        return 0;
    }
    refresh();
    endwin();
    return 0;
}
