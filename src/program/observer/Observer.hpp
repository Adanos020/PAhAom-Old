/**
 * @file src/program/observer/Observer.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "../game/entity/Entity.hpp"

namespace rr {

/// Class for the observer
    class Observer {
    public: enum Event {
                ITEM_EQUIP_FAILURE,
                ITEM_DISCOVERED,
                ITEM_DROPPED,
                ITEM_PICKED,
                ITEM_USED,
                INVENTORY_FULL,
                PLAYER_HUNGRY,
                PLAYER_STARVING,
                PLAYER_ATTACK_SUCCESS,
                PLAYER_ATTACK_FAILURE,
                PLAYER_DIES,
                NPC_ATTACK_SUCCESS,
                NPC_ATTACK_FAILURE,
                NPC_DIES
            };

            ////////////////////////////////////////////////////////////////////////
            /// \brief Virtual destructor.
            ////////////////////////////////////////////////////////////////////////
            virtual ~Observer() {}

            ////////////////////////////////////////////////////////////////////////
            /// \brief Reacts to a specific event. It can either do something with
            /// a given entity or just ignore it.
            ////////////////////////////////////////////////////////////////////////
            virtual void onNotify(Event, Entity*) = 0;
    };

/// Class for the subject
    class Subject {
    private: std::vector<Observer*> observers_;
    
    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Virtual destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Subject();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds the observer to the list.
             ////////////////////////////////////////////////////////////////////////
             void addObserver(Observer*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes the observer from the list.
             ////////////////////////////////////////////////////////////////////////
             void removeObserver(Observer*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Clears the list of observers.
             ////////////////////////////////////////////////////////////////////////
             void clear();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Notifies all the observers about an event related to a
             /// specific entity.
             ////////////////////////////////////////////////////////////////////////
             void notify(Observer::Event, Entity*);
    };

}

#endif // OBSERVER_HPP
