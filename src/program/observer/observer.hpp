/**
 * @file src/observer/observer.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef observer_hpp
#define observer_hpp

#include "../program/game/entities/entities.hpp"

namespace rr {

    class Observer {
    public:
        enum Event {
            ITEM_DISCOVERED
            ITEM_PICKED
            ITEM_DROPPED
        };
        void notify(Event, Entity*);
    };

    class Listener {
    public:
        void listen(Observer::Event, Entity*) = 0;
    };

}

#endif // observer_hpp
