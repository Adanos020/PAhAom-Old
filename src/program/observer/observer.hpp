/**
 * @file src/program/observer/observer.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef observer_hpp
#define observer_hpp

#include "../game/entities/entities.hpp"

namespace rr {

/// Class for the observer
    class Observer {
    public:
        enum Event {
            ITEM_DISCOVERED,
            ITEM_DROPPED,
            ITEM_PICKED,
            ITEM_USED
        };

        virtual ~Observer() {}
        virtual void onNotify(Event, Entity*) = 0;
    };

/// Class for the subject
    class Subject {
    private:
        std::vector<Observer*> observers_;
    public:
        ~Subject();

        void addObserver   (Observer*);
        void removeObserver(Observer*);
        void clear         ();
        void notify        (Observer::Event, Entity*);
    };

}

#endif // observer_hpp
