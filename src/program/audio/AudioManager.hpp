/**
 * @file src/program/audio/AudioManager.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <SFML/Audio.hpp>

#include "../observer/Observer.hpp"

#include "../game/entity/Entity.hpp"

namespace rr
{

    class AudioManager : public Observer, public sf::Listener
    {
        private: sf::Music music_;

                 ////////////////////////////////////////////////////////////////////////
                 /// \brief Reacts to a specific event. It can either do something with
                 /// a given entity or just ignore it.
                 ////////////////////////////////////////////////////////////////////////
         virtual void onNotify(Event, Entity*) override;

        public:  enum Song
                 {
                     MENU,
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
    };

}

#endif // AUDIO_MANAGER_HPP
