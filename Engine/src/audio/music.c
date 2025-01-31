#include "audio/music.h"

audio_music_s *audio_loadMusic(char* path)
{
    audio_music_s *music = Mix_LoadMUS(path);
    if (music == NULL) {
        printf("Failed To Load Music: %s\n", path);
        exit(EXIT_FAILURE);
    }
    return music;
}

void audio_playMusic(audio_music_s* music, int time)
{
    Mix_PlayMusic(music, time);
}

void audio_pauseMusic()
{
    Mix_PauseMusic();
}

void audio_resumeMusic()
{
    Mix_ResumeMusic();
}

void audio_stopMusic()
{
    Mix_HaltMusic();
}

void audio_destroyMusic(audio_music_s* music)
{
    Mix_FreeMusic(music);
}

