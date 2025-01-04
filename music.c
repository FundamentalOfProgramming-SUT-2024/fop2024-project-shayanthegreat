#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

int music_status;
void music_on(){
    if(music_status){
        return;
    }
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return ;
    }
    Mix_Music *music = Mix_LoadMUS("Music.mp3");
    if (music == NULL) {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
        return ;
    }
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
        return ;
    }
    music_status = 1;
}
void music_off(){
    Mix_Music *music = Mix_LoadMUS("Music.mp3");
    music_status = 0;
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}
