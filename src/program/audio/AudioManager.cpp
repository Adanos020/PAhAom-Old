/**
 * @file src/program/audio/AudioManager.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "AudioManager.hpp"

#include "../Settings.hpp"

namespace rr
{

    // PRIVATE

    void
    AudioManager::onNotify(Event event, Entity* entity)
    {
        switch (event)
        {
            case PLAYER_ATTACK_SUCCESS: playSound(ATTACK_HIT, Settings::sound.effects_volume);
                                        break;

            case PLAYER_ATTACK_FAILURE: playSound(ATTACK_MISS, Settings::sound.effects_volume);
                                        break;

            case NPC_ATTACK_SUCCESS   : playSound(ATTACK_HIT, Settings::sound.effects_volume);
                                        break;

            case NPC_ATTACK_FAILURE   : playSound(ATTACK_MISS, Settings::sound.effects_volume);
                                        break;

            default                   : break;
        }
    }

    // PUBLIC

    AudioManager::AudioManager()
    {
        music_.setLoop(true);
        music_.setVolume(Settings::sound.music_muted ? 0
                                                     : Settings::sound.music_volume);
    }

    void
    AudioManager::playMusic(Song song)
    {
        switch (song)
        {
            case MENU: music_.stop();
                       music_.openFromFile("data/music/menu.ogg");
                       music_.play();

            default  : break;
        }
    }

    void
    AudioManager::stopMusic()
    {
        music_.stop();
    }

    void
    AudioManager::pauseMusic()
    {
        music_.pause();
    }

    void
    AudioManager::setMusicVolume(float vol)
    {
        music_.setVolume(vol);
    }

    void
    AudioManager::playSound(SoundEffect sound, float volume)
    {
        switch (sound)
        {
            default: break;
        }
    }

}
