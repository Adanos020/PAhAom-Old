#ifndef item_h
#define item_h

#include <SFML/Graphics.hpp>

namespace rr {

    class Item {
      protected:
        int amount;
        double ID;
        bool equipable;
        bool disposable;
        std::string name;
        std::string description;
        std::string effects;
        std::string requirements;
        sf::FloatRect boundBox;
        sf::Texture skin;
        sf::VertexArray body;
      public:
        virtual ~Item() = default;
        virtual void draw(sf::RenderWindow&) = 0;
        virtual void editAmount(int) = 0;
        virtual void update() = 0;

        virtual double getID()                  {
            return ID;
        }
        virtual int getAmount()                 {
            return amount;
        }
        virtual bool isDisposable()             {
            return disposable;
        }
        virtual bool isEquipable()              {
            return equipable;
        }
        virtual std::string getName()           {
            return name;
        }
        virtual std::string getDescription()    {
            return description;
        }
        virtual sf::Texture getSkin()           {
            return skin;
        }
        virtual sf::VertexArray getBody()       {
            return body;
        }
    };

    class Potion :public Item {
      private:
        short bonus;
      public:
        Potion(double ID, std::string itemName, short icon, int am, short val, sf::Vector2f pos = sf::Vector2f(0, 0));
        ~Potion();

        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

    class Spell :public Item {
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

    class Book :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

    class Weapon :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

    class Food :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

    class Cash :public Item {
      private:
      public:
        virtual void draw(sf::RenderWindow&) override;
        virtual void editAmount(int) override;
        virtual void update() override;
    };

}

#endif
