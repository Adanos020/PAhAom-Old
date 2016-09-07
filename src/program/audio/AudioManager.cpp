/**
 * @file src/program/audio/AudioManager.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
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
        m_music.setLoop(true);
        m_music.setVolume(Settings::sound.music_muted ? 0
                                                     : Settings::sound.music_volume);
    }

    void
    AudioManager::playMusic(Song song)
    {
        switch (song)
        {
            case MENU: m_music.stop();
                       m_music.openFromFile("data/music/menu.ogg");
                       m_music.play();

            default  : break;
        }
    }

    void
    AudioManager::stopMusic()
    {
        m_music.stop();
    }

    void
    AudioManager::pauseMusic()
    {
        m_music.pause();
    }

    void
    AudioManager::setMusicVolume(float vol)
    {
        m_music.setVolume(vol);
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
