#include <stdio.h>
#include<stdlib.h>
#include<string.h>

char user_pass[500];
int main(){
    char filename[5000] = "/home/crk/projeh/user/";
    strcat(filename, "shayan");
    strcat(filename, "/pass.txt");
    FILE *file = fopen(filename, "r");
    fgets(user_pass, sizeof(user_pass), file);
    fclose(file);
    printf("%s", user_pass);
}