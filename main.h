#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include<time.h>
#include<locale.h>
#include <unistd.h>
#include<math.h>
#define N 1000
#define COLOR_ORANGE 8
#define COLOR_GOLD 9
#define COLOR_SILVER 10
#define COLOR_BRONZE 11
#define MAX_FOLDERS 100  // Maximum number of folders you can store in the array
#define MAX_NAME_LEN 256 // Maximum length of each folder name
typedef struct Userinfo{
    char user_name[5000], user_pass[5000], user_email[5000];
    int user_exp, user_point, user_gold, user_game;
} Userinfo;
typedef struct Position{
    int x, y;
} Position;
typedef struct food{
    int x, y, type, health;
    int time;
} food;
typedef struct gun{
    int x, y, type, damage;
} gun;
typedef struct gold{
    int x, y, type, amount;
} gold;
typedef struct spell{
    int x, y, type;
} spell;
typedef struct Player
{
    Position position;
    int health;
    int hunger;
    food food[5];
    int fooditem;
    int gold;
    int spell[3];
    int activespell[3];
    int gunnumber[5];
    int activegun;
    int point;
} Player;
typedef struct Room{
    Position position;
    int height, width;
    Position *enemy;
    int doornum;
    Position *door;
    int foodnum;
    food *food;
    int gunnum;
    gun *gun;
    //
    int golditem;
    gold *gold;
    int spellitem;
    spell *spell;
    //Position stair;
} Room;
typedef struct tile{
    int type;
    char symbol;
    Position DET;
    bool visit;
    // type -7 <
    // type -2 - |
    // type -1 #
    // type 0 .
    // type 1 = food;
    // type 2 = gun
    // type 3 = gold
    // type 4 = spell
    // type 6 = monster

} tile;

typedef struct Monster{
    int type;
    char symbol;
    Position position;
    int damage;
    int health;
    int roomnum;
    int follow;
    int pathfollow;
    bool active;
} Monster;

typedef struct Level{
    Room * rooms[6];
    tile map[200][200];
    Position stair;
    wchar_t** copy_map;
    int monstersnum;
    Monster * monsters[20];
} Level;
int Create_room(int level, Room *room, int number);
int Create_map();
int getroom(Position position);
void player_move(Player* User, int x, int y, int input);
void input_player(Player *User, int x);
void update_food(food foodi, Player *User);
void update_gun(gun GUN, Player *User);
void update_gold(gold gold, Player *User);
void BFS(int x, int y);
int draw_line(int level, Position A, Position B);
void update_map(Player *User, int input);
Player * init_player();
void menu_user();
wchar_t **copy_line(int n);
void print_line(int n, wchar_t **line);
void message(char *msg, int color);
WINDOW *Create_window(int width, int height);
void Show_food(food* FOOD, int count);
void Show_gun();
void attack(int level, int x);
void change_tile(int level, int x, int y, int type, char symbol);
int Get_monster(int level, int x, int y);
void EatFood(food food);
int max(int x, int y);
int min(int x, int y);
void stair_handle(int cnt);
int Create_stair(int level);
void replace(int x, int y);
bool empty(int x, int y);
void display_health();
void Show_spell();
void lister(int n, char folders[MAX_FOLDERS][MAX_NAME_LEN]);
void music_on(int x);
int Create_room_marg(int level, Room *room);
void Create_level_monster_marg(int level);
void Update_level_monster_marg(int level);
void create_X();
void MARG_LEVEL();
void update_map_marg(Player *User, int input);
void lose_function();
void print_large_text(int y, int x, const char *text);
void Update_user(Userinfo* userinfo);
int choose_mode();
void message2(char *msg, int color, int longer);
void print_save(int y, int x);
void save_function();
void message3(char *msg, int color);
extern Level levels[5];
extern int FLOOR, music_status, HEALTH, MAX_HEALTH;
extern int CHAMP_COLOR;
extern long long TIME_START;
extern Userinfo *userinfo;
extern Player *User;
extern int GLOBAL_INCREMENT_DAMAGE;
extern int GLOBAL_INCREMENT_SPEED;
#endif