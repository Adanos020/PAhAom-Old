#ifndef gui_h
#define gui_h

#include <SFML/Graphics.hpp>
#include <vector>
#include "../funcs/funcs.h"
#include "../game/item/item.h"

namespace rr {

    class Button;
    class Checkbox;
    class Image;
    class Item;
    class Slot;
    class Text;

    class Component {
    public:
        virtual ~Component() {}
        virtual bool containsMouseCursor(sf::RenderWindow&) = 0;
        virtual Text* getText() = 0;
        virtual void draw(sf::RenderWindow&) = 0;
        virtual void setPosition(sf::Vector2f) = 0;
        virtual void setSize(sf::Vector2f) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual sf::Vector2f getSize() = 0;
    };

    class Window {
    private:
        bool visible;

        sf::RectangleShape body;
        std::vector<Component*> components;

        Text* header;
    public:
        Window(std::string head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
        Window(std::wstring head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
        ~Window();

        void addComponent(Component*);
        void setVisible(bool);

        bool isVisible();
        sf::Vector2f getSize();
        sf::Vector2f getPosition();

        template<typename T>
        T* getComponent(unsigned index) {
            if (std::is_base_of<Component, T>::value) {
                if (std::is_base_of<Button, T>::value) {
                    for (unsigned i=0; i<components.size(); i++) {
                        if (instanceof<Button, Component>(components[i]) && !instanceof<Checkbox, Component>(components[i]) && !instanceof<Slot, Component>(components[i])) {
                            if (index--==0) return (T*)components[i];
                        }
                    }
                }
                for (unsigned i=0; i<components.size(); i++) {
                    if (instanceof<T, Component>(components[i])) {
                        if (index--==0) return (T*)components[i];
                    }
                }
            }
            else {
                puts("element of given type not found");
                return nullptr;
            }
            puts("element with a given index not found");
            return nullptr;
        }

        void draw(sf::RenderWindow&);
    };

    class Bar :public Component {
    private:
        sf::Vector2f position;
        sf::RectangleShape border;
        sf::RectangleShape bar;
    public:
        Bar(std::string plain, int max_length, sf::Color, sf::Vector2f pos);
        ~Bar();

        void setPosition(sf::Vector2f) override;
        void resize(float scale);

        void draw(sf::RenderWindow&) override;
    };


    class Button :public Component {
    protected:
        sf::RectangleShape body;
        sf::Color color;
        Text* text;
        Image* image;
    public:
        Button(sf::Vector2f position, std::string, unsigned chsize, sf::Color = sf::Color::White);
        Button(sf::Vector2f position, std::wstring, unsigned chsize, sf::Color = sf::Color::White);
        ~Button();

        bool containsMouseCursor(sf::RenderWindow&) override;
        Text* getText() override;
        sf::Vector2f getPosition() override;
        sf::Vector2f getSize() override;
        void setPosition(sf::Vector2f) override;

        void draw(sf::RenderWindow&) override;

        void setSize(sf::Vector2f) override {}
    };

    class Checkbox :public Button {
    private:
        sf::Vector2f position;
        bool checked;
    public:
        Checkbox(sf::Vector2f pos, std::string txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
        Checkbox(sf::Vector2f pos, std::wstring txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
        ~Checkbox();

        void check(bool b);
        bool isChecked();

        void draw(sf::RenderWindow& rw) override;
        void setPosition(sf::Vector2f) override;
    };


    class Image :public Component {
    private:
        sf::VertexArray body;
        sf::Texture skin;
        int icn;
    public:
        Image(sf::Vector2f position, int iconSize, std::string path, unsigned index);
        ~Image();

        void setPosition(sf::Vector2f) override;
        void setSize(sf::Vector2f) override;
        void change(unsigned index);
        void change(sf::VertexArray, sf::Texture);
        void scale(sf::Vector2f);
        void paint(sf::Color);
        void draw(sf::RenderWindow&) override;

        sf::Texture getSkin();
        sf::VertexArray getBody();
        sf::Vector2f getPosition() override;
        sf::Vector2f getSize() override;

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText() override { return nullptr; }
    };

    class Slot :public Button {
    private:
        bool hollow;

        sf::Vector2f position;

        Image* itemSkin;
        Item* item;
    public:
        Slot(sf::Vector2f size, sf::Vector2f pos, int icon = 0, sf::Color = sf::Color(110, 110, 110, 128));
        ~Slot();

        Item* getItem();

        bool addItem(double ID, int amount);
        void removeItem(int);

        void setPosition(sf::Vector2f) override;
        void draw(sf::RenderWindow&) override;

        bool isEmpty();
    };

    class Switch :public Component {
    private:
        sf::RectangleShape body;
        Button* left;
        Button* right;
        Text* text;
        std::vector<std::wstring> options;
        unsigned counter;
    public:
        Switch(std::string lButton, std::string rButton, sf::Vector2f size, sf::Vector2f position);
        ~Switch();

        void setPosition(sf::Vector2f) override;
        virtual void setSize(sf::Vector2f) override;
        void buttonEvents(sf::RenderWindow&);

        void addOption(std::wstring);
        void setCurrentOption(std::wstring);
        std::wstring getCurrentOption();

        void draw(sf::RenderWindow&) override;

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText() override { return nullptr; }
        virtual sf::Vector2f getPosition() override { return left->getPosition(); }
        virtual sf::Vector2f getSize() override { return body.getSize(); }
    };

    class Text :public Component {
    private:
        sf::Font font;
        sf::Text text;
    public:
        Text(std::string, unsigned chsize = 30, sf::Color = sf::Color::White);
        Text(std::wstring, unsigned chsize = 30, sf::Color = sf::Color::White);
        Text(std::string, sf::Vector2f position, unsigned chsize = 30, sf::Color = sf::Color::White);
        Text(std::wstring, sf::Vector2f position, unsigned chsize = 30, sf::Color = sf::Color::White);

        void setPosition(sf::Vector2f) override;
        void setCharacterSize(unsigned);
        void setColor(sf::Color);
        void setString(std::string);
        void setString(std::wstring);

        sf::Vector2f getSize() override;
        sf::Vector2f getPosition() override;
        double getCharacterSize();
        sf::Color getColor();
        std::string getString();

        void draw(sf::RenderWindow&) override;

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText() override { return nullptr; }
        void setSize(sf::Vector2f) override {}
    };

}

#endif // gui_h
