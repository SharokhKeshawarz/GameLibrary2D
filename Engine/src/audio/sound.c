#include "audio/sound.h"

audio_sound_s *audio_loadSound(char* path)
{
    static int id = 0;
    audio_sound_s *sound = malloc(sizeof(audio_sound_s));

    sound->sound = Mix_LoadWAV(path);
    if (sound->sound == NULL) {
        printf("Failed To Load Sound: %s\n", path);
        exit(EXIT_FAILURE);
    }
    sound->id = id;
    id++;
    return sound;
}

void audio_playSound(audio_sound_s* sound, int time)
{
    Mix_PlayChannel(sound->id, sound->sound, time);
}

void audio_pauseSound(audio_sound_s* sound)
{
    Mix_Pause(sound->id);
}

void audio_resumeSound(audio_sound_s* sound)
{
    Mix_Resume(sound->id);
}

void audio_stopSound(audio_sound_s* sound)
{
    Mix_HaltChannel(sound->id);
}

void audio_destroySound(audio_sound_s* sound)
{
    Mix_FreeChunk(sound->sound);
    free(sound);
}
