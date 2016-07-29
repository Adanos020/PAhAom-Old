/**
 * @file src/program/gui/Menu.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef GUI_MENU_HPP
#define GUI_MENU_HPP

#include <vector>

#include "Component.hpp"
#include "Button.hpp"

namespace rr {

    class Menu : public Component {
    private: std::vector<Button> options_;
             sf::Vector2f        position_;

    public:  void                 addOption      (sf::String);
             void                 setOption      (unsigned index, sf::String);
             void                 removeOption   (unsigned index);
             void                 clear          ()                           { options_.clear(); }

             sf::String           getChosenOption(sf::RenderWindow&, sf::Event&);
             int                  getOptionCount () const                     { return options_.size(); }
             
             virtual void         draw           (sf::RenderWindow&) override;
             virtual void         setPosition    (sf::Vector2f)      override;
             virtual void         setSize        (sf::Vector2f)      override {}
             virtual sf::Vector2f getPosition    () const                     { return position_; }
             virtual sf::Vector2f getSize        () const                     { return sf::Vector2f(0, options_.size()*40); }

             Menu(sf::Vector2f position = sf::Vector2f(0, 0));
            ~Menu();
    };

}

#endif // GUI_MENU_HPP
