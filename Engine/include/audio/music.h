#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>

#define LOOP -1
#define ONCE 0

typedef Mix_Music audio_music_s;

audio_music_s *audio_loadMusic(char* path);

void audio_playMusic(audio_music_s* music, int time);
void audio_pauseMusic();
void audio_resumeMusic();
void audio_stopMusic();
void audio_destroyMusic(audio_music_s* music);

#endif
