#include <stdio.h>
#include <sys/stat.h>  
#include <stdlib.h>    
#include<ncurses.h>
#include<string.h>
#include<dirent.h>
#include "connect.h"

bool is_new(char *user_name){
    char folderName[5000] = "user/";
    strcat(folderName, user_name);
    DIR *dir = opendir(folderName);
    if (dir) {
        closedir(dir);
        return 0;
    }
    return 1;
}
void Create_user(Userinfo* userinfo){
    char filename[5000] = "user/";
    strcat(filename, userinfo->user_name);
    mkdir(filename, 0755);
    strcat(filename, "/email.txt");
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", userinfo->user_email);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/pass.txt");
    file = fopen(filename, "w");
    fprintf(file, "%s", userinfo->user_pass);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/exp.txt");
    file = fopen(filename, "w");
    userinfo->user_exp = time(NULL);
    fprintf(file, "%d", userinfo->user_exp);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/gold.txt");
    file = fopen(filename, "w");
    userinfo->user_gold = 0;
    fprintf(file, "%d", userinfo->user_gold);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/point.txt");
    file = fopen(filename, "w");
    userinfo->user_point = 0;
    fprintf(file, "%d", userinfo->user_point);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/game.txt");
    file = fopen(filename, "w");
    userinfo->user_game = 0;
    fprintf(file, "%d", userinfo->user_game);
    fclose(file);
}
void Fetch_user(char* user_name){
    char filename[5000] = "user/";
    strcat(filename, user_name);
    strcat(filename, "/pass.txt");
    FILE *file = fopen(filename, "r");
    fgets(userinfo->user_pass, 50, file);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, user_name);
    strcat(filename, "/email.txt");
    file = fopen(filename, "r");
    fgets(userinfo->user_email, 50, file);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/exp.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userinfo->user_exp);
    fclose(file);
    ///
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/gold.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userinfo->user_gold);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/point.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userinfo->user_point);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/game.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userinfo->user_game);
    fclose(file);
    return;
}

void Update_user(Userinfo* userinfo){
    userinfo->user_point += User->point * 2;
    userinfo->user_point += User->gold;
    userinfo->user_gold += User->gold;
    char filename[5000] = "user/";
    strcat(filename, userinfo->user_name);
    strcat(filename, "/gold.txt");
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d", userinfo->user_gold);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/point.txt");
    file = fopen(filename, "w");
    fprintf(file, "%d", userinfo->user_point);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, userinfo->user_name);
    strcat(filename, "/game.txt");
    file = fopen(filename, "w");
    userinfo->user_game++;
    fprintf(file, "%d", userinfo->user_game);
    fclose(file);
    return;
}


Userinfo Fetch_user2(char* user_name){
    char filename[5000] = "user/";
    Userinfo userx;
    strcat(filename, user_name);
    strcat(filename, "/exp.txt");
    FILE *file = fopen(filename, "r");
    fscanf(file, "%d", &userx.user_exp);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, user_name);
    strcat(filename, "/gold.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userx.user_gold);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, user_name);
    strcat(filename, "/point.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userx.user_point);
    fclose(file);
    strcpy(filename, "user/");
    strcat(filename, user_name);
    strcat(filename, "/game.txt");
    file = fopen(filename, "r");
    fscanf(file, "%d", &userx.user_game);
    fclose(file);
    return userx;
}