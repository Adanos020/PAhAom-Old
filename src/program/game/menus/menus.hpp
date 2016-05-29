/**
 * @file src/program/game/menus/menus.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef menus_h
#define menus_h

#include "../../observer/observer.hpp"
#include "../../gui/gui.hpp"
#include "../game.hpp"

namespace rr {

    class Game;

    class Player;

    class Text;
    class Window;

/// Class for the main menu
    class MainMenu {
    private:
        Text*   title_;
        Window* wMenu_;
    public:
         MainMenu();
        ~MainMenu();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the main menu's components
        void draw        (sf::RenderWindow&);
    };

/// Class for the pause menu
    class PauseMenu {
    private:
        sf::RectangleShape shadow_;
        Text*              title_;
        Window*            wMenu_;
    public:
         PauseMenu();
        ~PauseMenu();

    /// Opens the pause menu
        void open        ();

    /// Closes the pause menu window
        void close       ();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the pause menu's components
        void draw        (sf::RenderWindow&);

    /// Tells if the pause menu is open
        bool isOpen      ();
    };

/// Class for the player attributes window
    class Attributes {
    private:
        sf::RectangleShape shadow_;
        Window*            wAttr_;
    public:
         Attributes();
        ~Attributes();

    /// Opens the player attributes window
        void open        ();

    /// Closes the player attributes window
        void close       ();

    /// Updates the info about the player attributes
        void update      (Player*);

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the player attributes components
        void draw        (sf::RenderWindow&);

    /// Tells if the player attributes is open
        bool isOpen      ();
    };

/// Class for the book of spells
    class BookOfSpells {
    private:
        sf::RectangleShape shadow_;
        Window*            wBofs_;
    public:
         BookOfSpells();
        ~BookOfSpells();

    /// Opens the window of the book of spells
        void open        ();

    /// Closes the window of the book of spells
        void close       ();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the components of the window of the book of spells
        void draw        (sf::RenderWindow&);

    /// Tells if the window of the book of spells is open
        bool isOpen      ();
    };

/// Class for the player inventory
    class Inventory : public Observer {
    private:
        sf::RectangleShape shadow_;

        Window*            wInve_;
        Slot*              sCarryOn_[5];

        short              bronze_;
        short              silver_;
        short              gold_;
    public:
         Inventory();
        ~Inventory();

    /// Adds an item to the inventory
        bool addItem     (Item*);

    /// Opens the inventory window
        void open        ();

    /// Closes the inventory window
        void close       ();

    /// Clears the inventory
        void clear       ();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the inventory components
        void draw        (sf::RenderWindow&);

    /// Tells if the inventory is open
        bool isOpen      ();

        virtual void onNotify(Event, Entity*) override;
    };

/// Class for the task list
    class Quests {
    private:
        sf::RectangleShape shadow_;
        Window*            wQues_;
    public:
         Quests();
        ~Quests();

    /// Opens the task list window
        void open        ();

    /// Closes the task list window
        void close       ();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the task list components
        void draw        (sf::RenderWindow&);

    /// Tells if the task list is open
        bool isOpen      ();
    };

/// Class for the game map
    class GameMap {
    private:
        sf::RectangleShape shadow_;
        Window*            wGmap_;
    public:
         GameMap();
        ~GameMap();

    /// Opens the game map window
        void open        ();

    /// Closes the game map window
        void close       ();

    /// Handles the button events
        void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

    /// Draws the game map components
        void draw        (sf::RenderWindow&);

    /// Tells if the game map is open
        bool isOpen      ();
    };

}

#endif // menus_h
