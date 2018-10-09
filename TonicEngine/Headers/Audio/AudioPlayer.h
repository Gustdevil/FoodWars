#ifndef PROJECT_SWA_AUDIOPLAYER_H
#define PROJECT_SWA_AUDIOPLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();
    void setEffectVolume(int volume);
    void setMusicVolume(int volume);
    void playMusic(const char *path, int amountOfLoops);
    void playEffect(const char *path);
private:
    bool init();
};

#endif //PROJECT_SWA_AUDIOPLAYER_H