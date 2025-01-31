#include "monster.h"
bool is_adj(Position A, Position B) {
    int dx = abs(A.x - B.x);
    int dy = abs(A.y - B.y);
    return (dx <= 1 && dy <= 1);
}
void Create_level_monster(int level){
    int x = rand()%6+3;
    levels[level].monstersnum = x;
    for(int i = 0; i < x; i++){
        int type = rand() % 5;
        int roomnum = rand() % 6;
        Position position;
        position.x = levels[level].rooms[roomnum]->position.x+1+rand()%(levels[level].rooms[roomnum]->height-2);
        position.y = levels[level].rooms[roomnum]->position.y+1+rand()%(levels[level].rooms[roomnum]->width-2);
        while(levels[level].map[position.x][position.y].symbol != '.'){
            position.x = levels[level].rooms[roomnum]->position.x+1+rand()%(levels[level].rooms[roomnum]->height-2);
            position.y = levels[level].rooms[roomnum]->position.y+1+rand()%(levels[level].rooms[roomnum]->width-2);
        }
        levels[level].monsters[i] = malloc(sizeof(Monster *) * 1); 
        switch (type){
            case 0:
                levels[level].monsters[i] = Create_monster(0, 'D', roomnum, 5, 3, 0, 0, position);
                break;
            case 1:
                levels[level].monsters[i] = Create_monster(1, 'F', roomnum, 10, 5, 0, 0, position);
                break;
            case 2:
                levels[level].monsters[i] = Create_monster(2, 'G', roomnum, 15, 8, 1, 15, position);
                break;
            case 3:
                levels[level].monsters[i] = Create_monster(3, 'S', roomnum, 20, 8, 1, 1000000, position);
                break;
            case 4:
                levels[level].monsters[i] = Create_monster(4, 'U', roomnum, 30, 8, 1, 0, position);
                break;
        }
    }
}
void Create_level_monster_marg(int level){
    levels[level].monstersnum = 12;
    for(int i = 0; i < 12; i++){
        int type = rand() % 5;
        int roomnum = 0;
        Position position;
        position.x = levels[level].rooms[roomnum]->position.x+1+rand()%(levels[level].rooms[roomnum]->height-2);
        position.y = levels[level].rooms[roomnum]->position.y+1+rand()%(levels[level].rooms[roomnum]->width-2);
        while(levels[level].map[position.x][position.y].symbol != '.'){
            position.x = levels[level].rooms[roomnum]->position.x+1+rand()%(levels[level].rooms[roomnum]->height-2);
            position.y = levels[level].rooms[roomnum]->position.y+1+rand()%(levels[level].rooms[roomnum]->width-2);
        }
        levels[level].monsters[i] = malloc(sizeof(Monster *)); 
        switch (type){
            case 0:
                levels[level].monsters[i] = Create_monster(0, 'D', roomnum, 5, 3, 0, 0, position);
                break;
            case 1:
                levels[level].monsters[i] = Create_monster(1, 'F', roomnum, 10, 5, 0, 0, position);
                break;
            case 2:
                levels[level].monsters[i] = Create_monster(2, 'G', roomnum, 15, 8, 1, 15, position);
                break;
            case 3:
                levels[level].monsters[i] = Create_monster(3, 'S', roomnum, 20, 8, 1, 1000000, position);
                break;
            case 4:
                levels[level].monsters[i] = Create_monster(4, 'U', roomnum, 30, 8, 1, 0, position);
                break;
        }
    }
}
Monster * Create_monster(int type, char symbol, int roomnum, int health, int damage, int follow, int pathfollow, Position position){
    Monster * newmonster = malloc(1 * sizeof(Monster));
    newmonster->damage = damage;
    newmonster->follow = follow;
    newmonster->health = health;
    newmonster->symbol = symbol;
    newmonster->position = position;
    newmonster->type = type;
    newmonster->roomnum = roomnum;
    newmonster->pathfollow = pathfollow;
    newmonster->active = 0;
    return newmonster;
}

void Random_move(int level, Monster * monster){
    int x = rand()%4;
    switch(x){
        case 0: // UP
            if(levels[level].map[monster->position.x-1][monster->position.y].type == 0){
                monster->position.x--;
            }
            break;
        case 1: // DOWN
            if(levels[level].map[monster->position.x+1][monster->position.y].type == 0){
                monster->position.x++;
            }
            break;
        case 2: // LEFT
            if(levels[level].map[monster->position.x][monster->position.y-1].type == 0){
                monster->position.y--;
            }
            break;
        case 3: // RIGHT
            if(levels[level].map[monster->position.x][monster->position.y+1].type == 0){
                monster->position.y++;
            }
            break;
    }
}

void Better_move(int level, Monster *monster) {
    if (monster->pathfollow == 0) {
        return;
    }

    // Array representing 8 directions (N, NE, E, SE, S, SW, W, NW)
    int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    int closest_x = monster->position.x;
    int closest_y = monster->position.y;
    double min_distance = __DBL_MAX__; // Initialize to a large value

    for (int i = 0; i < 8; i++) {
        int new_x = monster->position.x + dx[i];
        int new_y = monster->position.y + dy[i];

        // Ensure the new position is valid and not blocked
        if (levels[level].map[new_x][new_y].type == 0) {
            // Calculate the Euclidean distance to the user
            int distance = abs(new_x - User->position.x) + abs(new_y - User->position.y);


            // Update the closest position if this distance is smaller
            if (distance < min_distance) {
                min_distance = distance;
                closest_x = new_x;
                closest_y = new_y;
            }
        }
    }

    // Check if the closest position is the same as the user's position
    if (closest_x == User->position.x && closest_y == User->position.y) {
        return;
    }

    // Move the monster to the closest position and decrement pathfollow
    if (closest_x != monster->position.x || closest_y != monster->position.y) {
        monster->position.x = closest_x;
        monster->position.y = closest_y;
        monster->pathfollow--;
    }
}

void Update_level_monster_marg(int level){
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->type == 4 && is_adj(User->position, levels[level].monsters[i]->position)){
            levels[level].monsters[i]->active = 1;
            levels[level].monsters[i]->pathfollow = 5;
        }
        if(levels[level].monsters[i]->type != 4){
            levels[level].monsters[i]->active = 1;
        }
    }
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->health <= 0 && levels[level].monsters[i]->type != -1){
            levels[level].monsters[i]->type = -1;
            User->point += 50;
        }
        if(levels[level].monsters[i]->type == -1){
            change_tile(level, levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, 0, '.');
        }
    }
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->type == -1){
            continue;
        }
        mvprintw(levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, ".");
        if(levels[level].monsters[i]->follow == 0){
            Random_move(level, levels[level].monsters[i]);
        }
        else{
            Better_move(level, levels[level].monsters[i]);
        }
        if(is_adj(levels[level].monsters[i]->position, User->position)){
            User->health -= levels[level].monsters[i]->damage;
            switch (levels[level].monsters[i]->type){
                case 0:
                    message3("Deamon attacked you!", 1);
                    break;
                case 1:
                    message3("Fire Breathing Monster attacked you!", 1);
                    break;
                case 2:
                    message3("Gaint attacked you!", 1);
                    break;
                case 3:
                    message3("Snake attacked you!", 1);
                    break;
                case 4: 
                    message3("Undeed attacked you!", 1);
                    break; 
                default :
                    break;
            }
        }
        mvprintw(levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, "%c", levels[level].monsters[i]->symbol);
        move(User->position.x, User->position.y);
    }
}
// void Better_move(int level, Monster * monster){
//     if(monster->pathfollow==0){
//         return ;
//     }
//     if(abs((monster->position.x-1)-User->position.x) < abs(monster->position.x-User->position.x) && levels[level].map[monster->position.x-1][monster->position.y].type == 0){
//         if(monster->position.x-1 == User->position.x && monster->position.y == User->position.y){
//             return;
//         }
//         monster->pathfollow--;
//         monster->position.x--;
//     }
//     // right
//     else if(abs((monster->position.x+1)-User->position.x) < abs(monster->position.x-User->position.x) && levels[level].map[monster->position.x+1][monster->position.y].type == 0){
//         if(monster->position.x+1 == User->position.x && monster->position.y == User->position.y){
//             return;
//         }
//         monster->pathfollow--;
//         monster->position.x++;
//     }
//     // up
//     else if(abs((monster->position.y-1)-User->position.y) < abs(monster->position.y-User->position.y) && levels[level].map[monster->position.x][monster->position.y-1].type == 0){
//         if(monster->position.x == User->position.x && monster->position.y-1 == User->position.y){
//             return;
//         }
//         monster->pathfollow--;
//         monster->position.y--;
//     }
//     // down
//     else if(abs((monster->position.y+1)-User->position.y) < abs(monster->position.y-User->position.y) && levels[level].map[monster->position.x][monster->position.y+1].type == 0){
//         if(monster->position.x == User->position.x && monster->position.y+1 == User->position.y){
//             return;
//         }
//         monster->pathfollow--;
//         monster->position.y++;
//     }
// }

void Update_level_monster(int level){
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->health <= 0 && levels[level].monsters[i]->type != -1){
            User->point += 50;
            levels[level].monsters[i]->type = -1;
        }
        if(levels[level].monsters[i]->type == -1){
            change_tile(level, levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, 0, '.');
        }
    }
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->roomnum == getroom(User->position)){
            switch (levels[level].monsters[i]->type){
                case 0:
                case 1:
                case 2:
                case 3:
                    levels[level].monsters[i]->active = 1;
                break;
                case 4:
                    if(levels[level].monsters[i]->type == 4 && is_adj(levels[level].monsters[i]->position, User->position) && levels[level].monsters[i]->active != 1){ 
                        levels[level].monsters[i]->active = 1;
                        levels[level].monsters[i]->pathfollow = 5;
                    }
                break;
            }
            
        }
        else{
            switch (levels[level].monsters[i]->type){
                case 0:
                case 1:
                    break;
                case 2:
                case 3:
                case 4:  
                    levels[level].monsters[i]->active = 0;
                break;
                default :
                    break;
            }
        }
    }
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(!levels[level].monsters[i]->active && !(levels[level].monsters[i]->type == 4 && levels[level].monsters[i]->roomnum == getroom(User->position))){
            continue;
        }
        if(levels[level].monsters[i]->type == -1){
            continue;
        }
        mvprintw(levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, ".");
        if(levels[level].monsters[i]->follow == 0){
            Random_move(level, levels[level].monsters[i]);
        }
        else{
            Better_move(level, levels[level].monsters[i]);
        }
        if(is_adj(levels[level].monsters[i]->position, User->position)){
            User->health -= levels[level].monsters[i]->damage;
            switch (levels[level].monsters[i]->type){
                case 0:
                    message3("Deamon attacked you!", 1);
                    break;
                case 1:
                    message3("Fire Breathing Monster attacked you!", 1);
                    break;
                case 2:
                    message3("Gaint attacked you!", 1);
                    break;
                case 3:
                    message3("Snake attacked you!", 1);
                    break;
                case 4: 
                    message3("Undeed attacked you!", 1);
                    break; 
                default :
                    break;
            }
        }
        mvprintw(levels[level].monsters[i]->position.x, levels[level].monsters[i]->position.y, "%c", levels[level].monsters[i]->symbol);
        move(User->position.x, User->position.y);
    }
}

int Get_monster(int level, int x, int y){
    for(int i = 0; i < levels[level].monstersnum; i++){
        if(levels[level].monsters[i]->type != -1 && levels[level].monsters[i]->position.x == x && levels[level].monsters[i]->position.y == y){
            return i;
        }
    }
    return -1;
}
void change_tile(int level, int x, int y, int type, char symbol){
    if(levels[level].map[x][y].type == 0){
        levels[level].map[x][y].type = type;
        levels[level].map[x][y].symbol = symbol;
        mvprintw(x, y, "%c", symbol);
    }
}

void attack(int level, int x){
    switch(User->activegun){
        case 0:
            for(int i = 0; i < levels[level].monstersnum; i++){
                if(is_adj(User->position, levels[level].monsters[i]->position)){
                    levels[level].monsters[i]->health -= (5) * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                    switch (levels[level].monsters[i]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                }
            }
            break;
        case 4:
            for(int i = 0; i < levels[level].monstersnum; i++){
                if(is_adj(User->position, levels[level].monsters[i]->position)){
                    levels[level].monsters[i]->health -= 10 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                    switch (levels[level].monsters[i]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                }
            }
            break;
        case 1:
            if(User->gunnumber[1] == 0){
                break;
            }
            User->gunnumber[1]--;
            while(1){
                if(x == KEY_UP){
                    int res;
                    for(int i = 1; i <= 5; i++){
                        res = Get_monster(level, User->position.x-i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x-5, User->position.y, 5, '$');
                    }
                    else{
                        levels[level].monsters[res]->health -= 12 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_DOWN){
                    int res;
                    for(int i = 1; i <= 5; i++){
                        res = Get_monster(level, User->position.x+i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x+5, User->position.y, 5, '$');
                    }
                    else{
                        levels[level].monsters[res]->health -= 12 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_LEFT){
                    int res;
                    for(int i = 1; i <= 5; i++){
                        res = Get_monster(level, User->position.x, User->position.y-i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y-5, 5, '$');
                    }
                    else{
                        levels[level].monsters[res]->health -= 12 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }

                    break;
                }
                else if(x == KEY_RIGHT){
                    int res;
                    for(int i = 1; i <= 5; i++){
                        res = Get_monster(level, User->position.x, User->position.y+i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y+5, 5, '$');
                    }
                    else{
                        levels[level].monsters[res]->health -= 12 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else{
                    break;
                }
            }
            break;
        case 2:
            if(User->gunnumber[2] == 0){
                break;
            }
            User->gunnumber[2]--;
            while(1){
                if(x == KEY_UP){
                    int res;
                    for(int i = 1; i <= 7; i++){
                        res = Get_monster(level, User->position.x-i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x-7, User->position.y, 5, '&');
                    }
                    else{
                        levels[level].monsters[res]->health -= 15 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_DOWN){
                    int res;
                    for(int i = 1; i <= 7; i++){
                        res = Get_monster(level, User->position.x+i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x+7, User->position.y, 5, '&');
                    }
                    else{
                        levels[level].monsters[res]->health -= 15 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_LEFT){
                    int res;
                    for(int i = 1; i <= 7; i++){
                        res = Get_monster(level, User->position.x, User->position.y-i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y-7, 5, '&');
                    }
                    else{
                        levels[level].monsters[res]->health -= 15 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }

                    break;
                }
                else if(x == KEY_RIGHT){
                    int res;
                    for(int i = 1; i <= 7; i++){
                        res = Get_monster(level, User->position.x, User->position.y+i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y+7, 5, '&');
                    }
                    else{
                        levels[level].monsters[res]->health -= 15 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }else{
                    break;
                }
            }
            break;
        case 3:
            if(User->gunnumber[3] == 0){
                break;
            }
            User->gunnumber[3]--;
            while(1){
                if(x == KEY_UP){
                    int res;
                    for(int i = 1; i <= 4; i++){
                        res = Get_monster(level, User->position.x-i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x-4, User->position.y, 5, '*');
                    }
                    else{
                        levels[level].monsters[res]->health -= 5 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_DOWN){
                    int res;
                    for(int i = 1; i <= 4; i++){
                        res = Get_monster(level, User->position.x+i, User->position.y);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x+4, User->position.y, 5, '*');
                    }
                    else{
                        levels[level].monsters[res]->health -= 5 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_LEFT){
                    int res;
                    for(int i = 1; i <= 4; i++){
                        res = Get_monster(level, User->position.x, User->position.y-i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y-4, 5, '*');
                    }
                    else{
                        levels[level].monsters[res]->health -= 5 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else if(x == KEY_RIGHT){
                    int res;
                    for(int i = 1; i <= 4; i++){
                        res = Get_monster(level, User->position.x, User->position.y+i);
                        if(res != -1){
                            break;
                        }
                    }
                    if(res == -1){
                        change_tile(level, User->position.x, User->position.y+4, 5, '*');
                    }
                    else{
                        levels[level].monsters[res]->health -= 5 * (1 + ((User->activespell[2]>0) | (GLOBAL_INCREMENT_DAMAGE > 0)));
                        switch (levels[level].monsters[res]->type){
                        case 0:
                        message3("You attacked Deamon!", 1);
                         break;
                        case 1:
                        message3("You attacked Fire Breathing Monster!", 1);
                        break;
                        case 2:
                        message3("You attacked Gaint!", 1);
                        break;
                        case 3:
                            message3("You attacked Snake!", 1);
                        break;
                        case 4: 
                            message3("You attacked Undeed!", 1);
                        break; 
                        default :
                            break;
                    }
                    }
                    break;
                }
                else{
                    break;
                }
            }
            break;
    }
}