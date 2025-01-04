#include <stdio.h>
#include <sys/stat.h>  
#include <stdlib.h>    
#include<ncurses.h>
#include<string.h>
#include<dirent.h>
bool is_new(char *user_name){
    char folderName[5000] = "/home/crk/test/";
    strcat(folderName, user_name);
    DIR *dir = opendir(folderName);
    if (dir) {
        closedir(dir);
        return 0;
    }
    return 1;
}
void Create_user(char *user_name, char *user_email, char *user_pass){
    char filename[5000] = "/home/crk/test/";
    strcat(filename, user_name);
    mkdir(filename, 0755);
    strcat(filename, "/email.txt");
    printf("%s", filename);
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", user_email);
    fclose(file);
    strcpy(filename, "/home/crk/test/");
    strcat(filename, user_name);
    strcat(filename, "/pass.txt");
    file = fopen(filename, "w");
    fprintf(file, "%s", user_pass);
    fclose(file);
}
bool is_ok(char* user_name, char* user_pass){
    char filename[5000] = "/home/crk/test/";
    strcat(filename, user_name);
    strcat(filename, "/pass.txt");
    FILE *file = fopen(filename, "r");
    char pass[5000];
    fgets(pass, 500, file);
    if(!strcmp(pass, user_pass)){
        return 1;
    }
    return 0;
}