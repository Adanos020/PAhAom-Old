/**
 * @file src/observer/observer_Observer.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "observer.hpp"

namespace rr {

    Observer::~Observer() {
        for (auto listener : listeners_) {
            delete listener;
        }
        listeners_.clear();
    }

    void Observer::initialize(Game* game) {
        for (auto level : game->getLevels()) {
            listeners_.push_back(level);
        }
    }

    void Observer::notify(Listener::Event event, Entity* entity) {
        for (auto listener : listeners_) {
            listener->listen(event, entity);
        }
    }

}
