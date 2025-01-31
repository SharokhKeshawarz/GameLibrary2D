#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

#define LOOP -1
#define ONCE 0

typedef struct audio_sound_s
{
    int id;
    Mix_Chunk* sound;
} audio_sound_s;

audio_sound_s *audio_loadSound(char* path);

void audio_playSound(audio_sound_s* sound, int time);
void audio_pauseSound(audio_sound_s* sound);
void audio_resumeSound(audio_sound_s* sound);
void audio_stopSound(audio_sound_s* sound);
void audio_destroySound(audio_sound_s* sound);

#endif
