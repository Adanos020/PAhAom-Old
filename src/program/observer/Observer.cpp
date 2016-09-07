/**
 * @file src/program/observer/observer_Observer.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Observer.hpp"

namespace rr
{

    Subject::~Subject()
    {
        clear();
    }

    void
    Subject::addObserver(Observer* observer)
    {
        for (auto obs : m_observers)
        {
            if (obs == observer)
                return;
        }
        m_observers.push_back(observer);
    }

    void
    Subject::removeObserver(Observer* observer)
    {
        for (unsigned i = 0; i < m_observers.size(); i++)
        {
            if (observer == m_observers[i])
            {
                m_observers.erase(m_observers.begin()+i);
                return;
            }
        }
    }

    void
    Subject::clear()
    {
        m_observers.clear();
    }

    void
    Subject::notify(Observer::Event event, Entity* entity)
    {
        for (auto observer : m_observers)
        {
            observer->onNotify(event, entity);
        }
    }

}
