/**
 * @file src/program/gui/gui.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef gui_h
#define gui_h

#include <SFML/Graphics.hpp>
#include <vector>
#include "../funcs/funcs.hpp"
#include "../game/entities/item/item.hpp"

namespace rr {

    class Button;
    class Checkbox;
    class Image;
    class Item;
    class Slot;
    class Text;
    class Window;

/// Abstract class for all the GUI components
    class Component {
    private:
        Component* parentComponent_;
    public:
    /// Virtual destructor
        virtual ~Component() {}

    /// Method telling if this component is touched by the mouse cursor
        virtual bool         containsMouseCursor(sf::RenderWindow&)  = 0;

    /// Method drawing the component on the screen
        virtual void         draw               (sf::RenderWindow&)  = 0;

    /// Sets the component's body's position
        virtual void         setPosition        (sf::Vector2f)       = 0;

    /// Sets the component's body's size
        virtual void         setSize            (sf::Vector2f)       = 0;

    /// Returns the component's body's position
        virtual sf::Vector2f getPosition        ()             const = 0;

    /// Returns the component's body's size
        virtual sf::Vector2f getSize            ()             const = 0;

    /// Sets the component's parent component
        void                 setParentComponent (Component* p)       { parentComponent_ = p; }

    /// Returns the component's parent component
        Component*           getParentComponent ()             const { return parentComponent_; }
    };

/// Class for a vertical or a horizontal bar component representing any value you assign it to
    class Bar : public Component {
    private:
        sf::RectangleShape border_;
        sf::RectangleShape bar_;
    public:
        enum Plain {
            HORIZONTAL,
            VERTICAL
        };
         Bar(Plain, int max_length, sf::Color, sf::Vector2f pos);
        ~Bar();

        void         setPosition        (sf::Vector2f)            override;
        void         setSize            (sf::Vector2f)            override;
        void         draw               (sf::RenderWindow&)       override;

        sf::Vector2f getPosition        ()                  const override { return border_.getPosition(); }
        sf::Vector2f getSize            ()                  const override { return border_.getSize(); }

        bool         containsMouseCursor(sf::RenderWindow&)       override { return false; }
    };

/// Class for a button component which by being clicked can cause any action you assign to it
    class Button : public Component {
    protected:
        sf::RectangleShape body_;
        Image*             image_;
        Text*              text_;
        bool               held_;
    public:
         Button(sf::Vector2f position, sf::String, unsigned chsize, sf::Color = sf::Color::White);
        ~Button();

        bool         containsMouseCursor(sf::RenderWindow&)       override;
        bool         isPressed          (sf::RenderWindow&, sf::Event&);
        bool         isHeld             ()                  const          { return held_; }
        Text*        getText            ()                  const          { return text_; }
        sf::Vector2f getPosition        ()                  const override { return body_.getPosition(); }
        sf::Vector2f getSize            ()                  const override { return body_.getSize(); }
        void         setPosition        (sf::Vector2f)            override;
        void         draw               (sf::RenderWindow&)       override;

        void         setSize            (sf::Vector2f)            override {}
    };

/// Class for a checkbox component which can be checked or unchecked, depending on the parity of the number of clicks performed on it
    class Checkbox : public Component {
    private:
        sf::RectangleShape body_;
        Image*             image_;
        Text*              text_;
        bool               checked_;
        bool               held_;
    public:
         Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
        ~Checkbox();

    /// Sets the checkbox checked or not, depending on the value of the given argument
        void         check(bool b);

        void         draw               (sf::RenderWindow& rw)       override;
        void         setPosition        (sf::Vector2f)               override;

        bool         containsMouseCursor(sf::RenderWindow&)          override;
        bool         isPressed          (sf::RenderWindow&, sf::Event&);
        sf::Vector2f getPosition        ()                     const override { return body_.getPosition(); }
        sf::Vector2f getSize            ()                     const override { return body_.getSize(); }

    /// Method telling if the checkbox is checked
        bool         isChecked          ()                     const          { return checked_; }

        Text*        getText            ()                     const          { return text_; }

        void         setSize            (sf::Vector2f)               override {}
    };

/// Class for an Image*component which can be loaded from a file
    class Image : public Component {
    private:
        sf::Sprite body_;
        int        icon_;
    public:
         Image(sf::Vector2f position, sf::Texture&, int iconSize, unsigned index);
        ~Image();

        void          setPosition         (sf::Vector2f)      override;
        void          setSize             (sf::Vector2f)      override;

    /// Changes the icon index
        void          setIconIndex        (unsigned index);

    /// Changes the texture
        void          setTexture          (sf::Texture&);

    /// Method scaling the body's size
        void          scale               (sf::Vector2f);

    /// Method painting the body to a given color
        void          paint               (sf::Color);

        void          draw                (sf::RenderWindow&) override;

    /// Returns the image's body
        sf::Sprite    getBody             ()                  const          { return body_; }

        sf::Vector2f  getPosition         ()                  const override { return body_.getPosition(); }
        sf::Vector2f  getSize             ()                  const override { return sf::Vector2f(body_.getGlobalBounds().width, body_.getGlobalBounds().height); }

        virtual bool  containsMouseCursor (sf::RenderWindow&) override       { return false; }
    };

/// Class for a ScrollBar component
    class ScrollBar : public Component {
    public:
        enum Plain {
            HORIZONTAL,
            VERTICAL
        } plain_;
    private:
        sf::RectangleShape border_;
        sf::Vector2f       valueLimit_;
        Button             indicator_;
        Button             bLeft_;
        Button             bRight_;
        Text*              label_;
        float              value_;
    public:
         ScrollBar(Plain, sf::Vector2f position, float length, sf::Vector2f min_max = sf::Vector2f(0, 100));
        ~ScrollBar();

        void         setPosition        (sf::Vector2f)      override;
        void         setSize            (sf::Vector2f)      override;

    /// Sets the actual value of the scroll bar
        void         setValue           (int);
        void         draw               (sf::RenderWindow&) override;
        void         buttonEvents       (sf::RenderWindow&, sf::Event&);

        sf::Vector2f getPosition        ()                  const override { return bLeft_.getPosition(); }
        sf::Vector2f getSize            ()                  const override { return border_.getSize(); }
        Text*        getText            ()                  const          { return label_; }

    /// Returns the actual value of the scroll bar
        int          getValue           ()                  const          { return value_; }

        virtual bool containsMouseCursor(sf::RenderWindow&) override       { return false; }
    };

/// Class for a slot component which can contain any instance of the class Item
    class Slot : public Component {
    private:
        sf::RectangleShape body_;
        Image*             image_;
        Item*              item_;
        Text*              text_;
        bool               hollow_;
        bool               held_;
    public:
         Slot(sf::Vector2f size, sf::Vector2f pos, int icon = 0, sf::Color = sf::Color(110, 110, 110, 128));
        ~Slot();

    /// Adds an item to the slot
        bool         addItem            (Item*);

    /// Removes the item from the slot
        void         removeItem         (int);

    /// Clears the slot
        void         clear              ();

        void         setPosition        (sf::Vector2f)      override;
        void         draw               (sf::RenderWindow&) override;

        bool         containsMouseCursor(sf::RenderWindow&) override;
        bool         isPressed          (sf::RenderWindow&, sf::Event&);
        bool         isHeld             ()                  const          { return held_; }
        Text*        getText            ()                  const          { return text_; }
        sf::Vector2f getPosition        ()                  const override { return body_.getPosition(); }
        sf::Vector2f getSize            ()                  const override { return body_.getSize(); }

    /// Returns the item contained in the slot
        Item*        getItem            ()                  const          {    if (!hollow_)
                                                                                    return item_;
                                                                                return nullptr;
                                                                           }

    /// Method telling if the slot is empty
        bool         isEmpty            ()             const         { return hollow_; }
        void         setSize            (sf::Vector2f) override      {}
    };

/// Class for a switch component which can contain as many options you add to it and switch between them
    class Switch : public Component {
    private:
        sf::RectangleShape      body_;
        std::vector<sf::String> options_;
        Button                  left_;
        Button                  right_;
        Text*                   text_;
        mutable unsigned        counter_;
    public:
         Switch(sf::Vector2f size, sf::Vector2f position);
        ~Switch();

        void                 setPosition        (sf::Vector2f)            override;
        void                 setSize            (sf::Vector2f)            override;

    /// Method for handling the button events
        void                 buttonEvents       (sf::RenderWindow&, sf::Event&);

    /// Adds an option to the switch
        void                 addOption          (sf::String);

    /// Sets the current option
        void                 setCurrentOption   (sf::String);

        void                 draw               (sf::RenderWindow&)       override;

    /// Returns the current option
        sf::String           getCurrentOption   ()                  const          { return options_[counter_]; }
        virtual sf::Vector2f getPosition        ()                  const override { return left_.getPosition(); }
        virtual sf::Vector2f getSize            ()                  const override { return body_.getSize(); }

        virtual bool         containsMouseCursor(sf::RenderWindow&)       override { return false; }
        virtual Text*        getText            ()                  const          { return text_; }
    };

/// A class for a text component
    class Text : public Component {
    private:
        sf::Text text_;
    public:
         Text(sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Bold);
         Text(sf::Vector2f position, sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White, sf::Text::Style = sf::Text::Bold);
        ~Text();

        void            setPosition        (sf::Vector2f)            override;

    /// Wraps the text
        void            wrap               (float width);

    /// Sets the text's character size
        void            setCharacterSize   (unsigned c)                       { text_.setCharacterSize(c); }

    /// Sets the text's color
        void            setColor           (sf::Color c)                      { text_.setColor(c); }

    /// Sets the text's string
        void            setString          (sf::String s)                     { text_.setString(s); }

    /// Sets the text's font
        void            setFont            (sf::Font f)                       { text_.setFont(f); }

    /// Sets the text's style
        void            setStyle           (sf::Text::Style s)                { text_.setStyle(s); }

        sf::Vector2f    getSize            ()                  const override { return sf::Vector2f(text_.getGlobalBounds().width, text_.getGlobalBounds().height); }
        sf::Vector2f    getPosition        ()                  const override { return text_.getPosition(); }

    /// Returns the text's character size
        int             getCharacterSize   ()                  const          { return text_.getCharacterSize(); }

    /// Returns the text's color
        sf::Color       getColor           ()                  const          { return text_.getColor(); }

    /// Returns the text's string
        sf::String      getString          ()                  const          { return text_.getString(); }

    /// Returns the text style
        sf::Text::Style getStyle           ()                  const          { return (sf::Text::Style)text_.getStyle(); }

        void            draw               (sf::RenderWindow&)       override;

        virtual bool    containsMouseCursor(sf::RenderWindow&)       override { return false; }
        void            setSize            (sf::Vector2f)            override {}
    };

/// Class for an internal window component which also can be a component of another internal window component
    class Window : public Component {
    private:
        sf::RectangleShape      body_;
        Text*                   header_;
        std::vector<Component*> components_;
        bool                    visible_;
    public:
         Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
        ~Window();

    /// Adds a given component to the internal window
        void         addComponent      (Component*, bool attached);

    /// Sets the internal window visible or not, depending on the value of the given argument
        void         setVisible        (bool);

    /// Sets the internal window's title
        void         setTitle          (sf::String title)                  { header_->setString(title); }

        void         setPosition       (sf::Vector2f)             override;
        void         setSize           (sf::Vector2f siz)         override { body_.setSize(siz); }
        void         draw              (sf::RenderWindow&)        override;

    /// Method telling if the internal window is visible
        bool         isVisible         ()                   const          { return visible_; }

        sf::Vector2f getSize           ()                   const override { return body_.getSize(); }
        sf::Vector2f getPosition       ()                   const override { return body_.getPosition(); }

    /// Returns the internal window's component of a given type and index
        template<typename T>
        T*            getComponent      (unsigned index)     const          {   if (std::is_base_of<Component, T>::value) {
                                                                                   for (unsigned i=0; i<components_.size(); i++) {
                                                                                       if (instanceof<T, Component>(components_[i])) {
                                                                                           if (index-- == 0)
                                                                                                return (T*)components_[i];
                                                                                       }
                                                                                   }
                                                                               } else {
                                                                                   puts("element of given type not found");
                                                                                   return nullptr;
                                                                               }
                                                                               puts("element with a given index not found");
                                                                               return nullptr;
                                                                           }

        bool         containsMouseCursor(sf::RenderWindow&)       override { return false; }
        Text*        getText()                              const          { return header_; }

    /// Opeartor overload allowing to add the attached components without calling the addComponent method manually
        Window& operator+=(Component* c) {
            addComponent(c, true);
            return *this;
        }
    };

}

#endif // gui_h
