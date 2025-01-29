#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "music.h"
#include "main.h"
int music_status;
void music_on(int x){
    if(music_status == x || x == 0){
        return;
    }
    char musicfile[500];
    if(x == 1){
        strcpy(musicfile, "music1.mp3");
    }
    else{
        strcpy(musicfile, "music2.mp3");
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return ;
    }
    Mix_Music *music = Mix_LoadMUS(musicfile);
    if (music == NULL) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
        return ;
    }
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        return ;
    }
    music_status = x;
}
void music_off(){
    char musicfile[500];
    if(music_status == 1){
        strcpy(musicfile, "music1.mp3");
    }
    else if(music_status == 2){
        strcpy(musicfile, "music2.mp3");
    }
    else{
        return ;
    }
    music_status = 0;
    Mix_Music *music = Mix_LoadMUS(musicfile);
    music_status = 0;
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}