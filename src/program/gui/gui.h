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
    class Window;

    class Component {
    protected:
        Component* parent;
    public:
        virtual ~Component() = 0;
        virtual bool containsMouseCursor(sf::RenderWindow&) = 0;
        virtual Text* getText() = 0;
        virtual void draw(sf::RenderWindow&) = 0;
        virtual void setPosition(sf::Vector2f) = 0;
        virtual void setSize(sf::Vector2f) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual sf::Vector2f getSize() = 0;
        virtual Component* getParentComponent() = 0;
    };

    class Window :public Component {
    private:
        bool visible;

        sf::RectangleShape body;
        std::vector<Component*> components;

        Text* header;
    public:
        Window(Component* parentComponent, std::wstring head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
        ~Window();

        void addComponent(Component*);
        void setVisible(bool);
        void setPosition(sf::Vector2f pos) override { body.setPosition(pos); }
        void setSize(sf::Vector2f siz)     override { body.setSize(siz); }

        void draw(sf::RenderWindow&) override;

        bool isVisible()                         { return visible; }
        sf::Vector2f getSize()          override { return body.getSize(); }
        sf::Vector2f getPosition()      override { return body.getPosition(); }
        Component* getParentComponent() override { return parent; }

        template<typename T>
        T* getComponent(unsigned index) {
            if (std::is_base_of<Component, T>::value) {
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

        bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        Text* getText()                             override { return nullptr; }
    };

    class Bar :public Component {
    private:
        sf::Vector2f position;
        sf::RectangleShape border;
        sf::RectangleShape bar;
    public:
        Bar(Component* parentComponent, std::string plain, int max_length, sf::Color, sf::Vector2f pos);
        ~Bar();

        void setPosition(sf::Vector2f) override;
        void resize(float scale);
        void draw(sf::RenderWindow&)   override;

        Component* getParentComponent() override { return parent; }
    };


    class Button :public Component {
    protected:
        sf::RectangleShape body;
        sf::Color color;
        Text* text;
        Image* image;
    public:
        Button(Component* parentComponent, sf::Vector2f position, std::wstring, unsigned chsize, sf::Color = sf::Color::White);
        ~Button();

        bool containsMouseCursor(sf::RenderWindow&) override;
        Text* getText()                             override;
        sf::Vector2f getPosition()                  override;
        sf::Vector2f getSize()                      override;
        Component* getParentComponent()             override { return parent; }

        void setPosition(sf::Vector2f) override;
        void draw(sf::RenderWindow&)   override;

        void setSize(sf::Vector2f) override {}
    };

    class Checkbox :public Component {
    private:
        sf::RectangleShape body;
        sf::Color color;
        sf::Vector2f position;

        Text* text;
        Image* image;

        bool checked;
    public:
        Checkbox(Component* parentComponent, sf::Vector2f pos, std::wstring txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
        ~Checkbox();

        void check(bool b);
        void draw(sf::RenderWindow& rw) override;
        void setPosition(sf::Vector2f)  override;

        bool containsMouseCursor(sf::RenderWindow&) override;
        sf::Vector2f getPosition()                  override { return body.getPosition(); }
        sf::Vector2f getSize()                      override { return body.getSize(); }
        bool isChecked()                                     { return checked;}
        Component* getParentComponent()             override { return parent; }
        Text* getText()                             override { return text; }

        void setSize(sf::Vector2f) override {}
    };


    class Image :public Component {
    private:
        sf::VertexArray body;
        sf::Texture skin;
        int icn;
    public:
        Image(Component* parentComponent, sf::Vector2f position, int iconSize, std::string path, unsigned index);
        ~Image();

        void setPosition(sf::Vector2f) override;
        void setSize(sf::Vector2f)     override;
        void change(unsigned index);
        void change(sf::VertexArray, sf::Texture);
        void scale(sf::Vector2f);
        void paint(sf::Color);
        void draw(sf::RenderWindow&)   override;

        sf::Texture getSkin()                    { return skin; }
        sf::VertexArray getBody()                { return body; }
        sf::Vector2f getPosition()      override { return body[0].position; }
        sf::Vector2f getSize()          override { return sf::Vector2f(body[1].position.x-body[0].position.x, body[2].position.y-body[1].position.y); }
        Component* getParentComponent() override { return parent; }

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText()                             override { return nullptr; }
    };

    class Slot :public Component {
    private:
        bool hollow;

        sf::RectangleShape body;
        sf::Color color;
        sf::Vector2f position;

        Text* text;
        Image* itemSkin;
        Image* image;
        Item* item;
    public:
        Slot(Component* parentComponent, sf::Vector2f size, sf::Vector2f pos, int icon = 0, sf::Color = sf::Color(110, 110, 110, 128));
        ~Slot();

        bool addItem(double ID, int amount);
        void removeItem(int);
        void setPosition(sf::Vector2f) override;
        void draw(sf::RenderWindow&)   override;

        bool containsMouseCursor(sf::RenderWindow&) override;
        Text* getText()                             override { return nullptr; }
        sf::Vector2f getPosition()                  override { return body.getPosition(); }
        sf::Vector2f getSize()                      override { return body.getSize(); }
        Item* getItem()                                      { if (!hollow) return item; return nullptr; }
        bool isEmpty()                                       { return hollow; }
        Component* getParentComponent()             override { return parent; }

        void setSize(sf::Vector2f) override {}
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
        Switch(Component* parentComponent, std::wstring lButton, std::wstring rButton, sf::Vector2f size, sf::Vector2f position);
        ~Switch();

        void setPosition(sf::Vector2f) override;
        void setSize(sf::Vector2f)     override;
        void buttonEvents(sf::RenderWindow&);
        void addOption(std::wstring);
        void setCurrentOption(std::wstring);
        void draw(sf::RenderWindow&)   override;

        std::wstring getCurrentOption()             { return options.at(counter); }
        virtual sf::Vector2f getPosition() override { return left->getPosition(); }
        virtual sf::Vector2f getSize()     override { return body.getSize(); }
        Component* getParentComponent()    override { return parent; }

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText()                             override { return nullptr; }
    };

    class Text :public Component {
    private:
        sf::Text text;
    public:
        Text(Component* parentComponent, std::wstring, unsigned chsize = 30, sf::Color = sf::Color::White);
        Text(Component* parentComponent, std::wstring, sf::Vector2f position, unsigned chsize = 30, sf::Color = sf::Color::White);
        ~Text();

        void setPosition(sf::Vector2f) override;
        void setCharacterSize(unsigned);
        void setColor(sf::Color);
        void setString(std::string);
        void setString(std::wstring);

        sf::Vector2f getSize()          override { return sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height); }
        sf::Vector2f getPosition()      override { return text.getPosition(); }
        double getCharacterSize()                { return text.getCharacterSize(); }
        sf::Color getColor()                     { return text.getColor(); }
        std::string getString()                  { return text.getString(); }
        Component* getParentComponent() override { return parent; }

        void draw(sf::RenderWindow&) override;

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText()                             override { return nullptr; }
        void setSize(sf::Vector2f)                          override {}
    };

}

#endif // gui_h
