#ifndef PROJECT_SWA_AUDIO_H
#define PROJECT_SWA_AUDIO_H

#include <SDL2/SDL.h>
#include "AudioPlayer.h"
#include <string>
#include <map>

class AudioFacade {
public:
    AudioFacade();
    ~AudioFacade();
    int getEffectVolume();
    int getMusicVolume();
    void setEffectVolume(int volume);
    void setMusicVolume(int volume);
    void playMusic(const char* filename, int amountOfLoops);
    void playEffect(const char* filename);
    void addAudio(const char* key,const char* path);
private:
    std::map<std::string, std::string> *_audioMap = nullptr;
    AudioPlayer *_audioPlayer = nullptr;
    void init();
    const char* getAudio(const char* audioName);
};

#endif //PROJECT_SWA_AUDIO_H