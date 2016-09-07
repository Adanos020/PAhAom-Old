/**
 * @file src/program/gui/Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "Text.hpp"

namespace rr
{

    Text::Text(sf::String str, sf::Font& font, unsigned chsize, sf::Color color, sf::Text::Style style)
    {
        m_text.setFont            (font);
        m_text.setCharacterSize   (chsize);
        m_text.setString          (str);
        m_text.setFillColor       (color);
        m_text.setStyle           (style);
        m_text.setOutlineColor    (sf::Color::Black);
        m_text.setOutlineThickness((float) chsize/20.f);
    }

    Text::Text(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color color, sf::Text::Style style)
    {
        m_text.setFont            (font);
        m_text.setPosition        (pos);
        m_text.setCharacterSize   (chsize);
        m_text.setString          (str);
        m_text.setFillColor       (color);
        m_text.setStyle           (style);
        m_text.setOutlineColor    (sf::Color::Black);
        m_text.setOutlineThickness((float) chsize/20.f);
    }

    void
    Text::setPosition(sf::Vector2f pos)
    {
        m_text.setPosition(pos);
    }

    void
    Text::wrap(float width)
    {
        sf::String text         = m_text.getString();
        unsigned   offset       = 0;
        bool       first        = true;
        unsigned   wordBegining = 0;

        for (unsigned pos = 0; pos < text.getSize(); pos++)
        {
            if (text[pos] == '\n')
            {
                offset = 0;
                first  = true;
                continue;
            }
            else if (text[pos] == ' ')
            {
                wordBegining = pos;
                first        = false;
            }

            offset += m_text.getFont()->getGlyph(text[pos], m_text.getCharacterSize(), m_text.getStyle() == sf::Text::Bold).advance;

            if (!first && offset > width)
            {
                pos       = wordBegining;
                text[pos] = '\n';
                first     = true;
                offset    = 0;
            }
        }

        m_text.setString(text);
    }

    void
    Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_text, states);
    }

}
