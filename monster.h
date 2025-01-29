#ifndef MONSTER_H
#define MONSTER_H

#include "main.h"

void Create_level_monster();
Monster * Create_monster(int type, char symbol, int roomnum, int health, int damage, int follow, int pathfollow, Position position);
void Update_level_monster(int level);
void Random_move(int level, Monster * monster);
bool is_adj(Position A, Position B);
void attack(int level, int x);
void change_tile(int level, int x, int y, int type, char symbol);
int Get_monster(int level, int x, int y);
void Create_level_monster_marg(int level);
void Update_level_monster_marg(int level);
void MARG_LEVEL();

#endif