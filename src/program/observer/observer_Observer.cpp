/**
 * @file src/program/observer/observer_Observer.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "observer.hpp"
#include "../game/menus/menus.hpp"

namespace rr {

    Subject::~Subject() {
        clear();
    }

    void Subject::addObserver(Observer* observer) {
        for (auto obs : observers_) {
            if (obs == observer)
                return;
        }
        observers_.push_back(observer);
    }

    void Subject::removeObserver(Observer* observer) {
        for (unsigned i=0; i<observers_.size(); i++) {
            if (observer == observers_[i]) {
                observers_.erase(observers_.begin()+i);
                return;
            }
        }
    }

    void Subject::clear() {
        observers_.clear();
    }

    void Subject::notify(Observer::Event event, Entity* entity) {
        for (auto observer : observers_) {
            observer->onNotify(event, entity);
        }
    }

}
