/**
 * @file src/observer/observer.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef observer_hpp
#define observer_hpp

#include "../game/entities/entities.hpp"

namespace rr {

    class Listener {
    public:
        enum Event {
            ITEM_DISCOVERED,
            ITEM_PICKED,
            ITEM_DROPPED
        };

        virtual ~Listener() {}
        virtual void listen(Event, Entity*) = 0;
    };

    class Observer {
    private:
        std::vector<Listener*> listeners_;
    public:
        ~Observer();
        void initialize();
        void notify    (Listener::Event, Entity*);
    };

}

#endif // observer_hpp
