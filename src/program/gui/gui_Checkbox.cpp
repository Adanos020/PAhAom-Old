/**
 * @file src/program/gui/Checkbox.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "gui.h"

#include <iostream>

extern sf::Font font_Unifont;

namespace rr {

	Checkbox::Checkbox(Component* parentComponent, sf::Vector2f pos, sf::String txt, int chsize, sf::Color c) {
		parent = parentComponent;

		position = pos;

		body.setSize(sf::Vector2f(35, 35));
		body.setPosition(pos);
		body.setFillColor(c);
		body.setOutlineColor(sf::Color(c.r+20, c.g+20, c.b+20));
		body.setOutlineThickness(5);

		image = new Image(this, pos, 14, "data/graphics/gui.png", 1);
		text = new Text(this, sf::Vector2f(0, 0), txt, font_Unifont, chsize);
		text->setPosition(sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y));
	}

	Checkbox::~Checkbox() {
		delete image;
		delete text;
	}

	void Checkbox::check(bool b) {
		checked = b;
	}

	void Checkbox::setPosition(sf::Vector2f pos) {
		body.setPosition(pos);
		text->setPosition(sf::Vector2f(pos.x+45, pos.y+body.getSize().y/2-text->getSize().y));
		image->setPosition(pos);
	}

	void Checkbox::draw(sf::RenderWindow& rw) {
		rw.draw(body);
		if (checked) image->draw(rw);
		text->draw(rw);
	}

	bool Checkbox::containsMouseCursor(sf::RenderWindow& rw) {
		if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
			body.setFillColor(sf::Color(128, 128, 128, 255));
			return true;
		}
		body.setFillColor(sf::Color(128, 128, 128, 128));
		return false;
	}

}
