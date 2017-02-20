/**
 * @file src/program/AudioManager.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "AudioManager.hpp"

#include "Settings.hpp"

namespace rr
{

    // PRIVATE

    void
    AudioManager::onNotify(Event event, Entity*, sf::String)
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
        m_music.setVolume(Settings::sound.music_muted ? 0 : Settings::sound.music_volume);
    }

    void
    AudioManager::playMusic(Song song)
    {
        m_song = song;
        switch (song)
        {
            case NONE:
            {
                m_music.stop();
            }
            break;

            case MENU:
            {
                m_music.stop();
                m_music.openFromFile("data/music/menu.ogg");
                m_music.play();
            }
            break;

            case PRISON:
            {
                m_music.stop();
                m_music.openFromFile("data/music/prison.ogg");
                m_music.play();
            }
            break;

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
    AudioManager::playSound(SoundEffect sound, float)
    {
        switch (sound)
        {
            default: break;
        }
    }

    AudioManager::Song
    AudioManager::getCurrentSong() const
    {
        return m_song;
    }

}
