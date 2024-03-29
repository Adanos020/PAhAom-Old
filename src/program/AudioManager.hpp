/**
 * @file src/program/AudioManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <SFML/Audio.hpp>

#include "Observer.hpp"

#include "game/Entity.hpp"

namespace rr
{

    class AudioManager : public Observer, public sf::Listener
    {
        private: sf::Music m_music;

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Reacts to a specific event. It can either do something with
                 /// a given entity or just ignore it.
                 ////////////////////////////////////////////////////////////////////////
         virtual void onNotify(Event, Entity*, sf::String) override;

        public:  enum Song
                 {
                     NONE,
                     MENU,
                     PRISON,
                     BOSSFIGHT,
                     DEATH
                 };
                 enum SoundEffect
                 {
                     ATTACK_HIT,
                     ATTACK_MISS,
                     STEP
                 };

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Regular constructor.
                 ////////////////////////////////////////////////////////////////////////
                 AudioManager();

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Sets and starts playing a chosen song.
                 ////////////////////////////////////////////////////////////////////////
                 void playMusic(Song);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Stops playing the music.
                 ////////////////////////////////////////////////////////////////////////
                 void stopMusic();

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Pauses the music.
                 ////////////////////////////////////////////////////////////////////////
                 void pauseMusic();

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Sets the music volume.
                 ////////////////////////////////////////////////////////////////////////
                 void setMusicVolume(float);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Plays a given sound.
                 ////////////////////////////////////////////////////////////////////////
                 void playSound(SoundEffect, float volume);

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Returns the current song playing.
                 ////////////////////////////////////////////////////////////////////////
                 Song getCurrentSong() const;

    private:     Song m_song;
    };

}
