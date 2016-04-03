/**
 * @file src/program/game/Game.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "game.h"

#include <iostream>

namespace rr {

	Game::Game(sf::RenderWindow& rw) {
		mainMenu = new MainMenu(rw);
		pauseMenu = new PauseMenu(rw);
		hud = new HUD(rw);
		player = new Player(sf::Vector2f(0, 0));

		potions.push_back(new Potion(Potion::Effect::HEALING, Potion::Size::BIG, 1, sf::Vector2f(200, 200)));
		potions.push_back(new Potion(Potion::Effect::DEXTERITY, Potion::Size::MEDIUM, 1, sf::Vector2f(400, 200)));
		potions.push_back(new Potion(Potion::Effect::POISON, Potion::Size::SMALL, 1, sf::Vector2f(600, 200)));

		paused = false;
		started = false;
	}

	Game::~Game() {
		delete mainMenu;
		delete pauseMenu;
		delete hud;
		delete player;
	}

	void Game::draw(sf::RenderWindow& rw, sf::View& v) {
		if (!started) {
			rw.setView(rw.getDefaultView());
			mainMenu->draw(rw);
			rw.setView(v);
		} else {
			for (auto x : potions)
				x->draw(rw);
			player->draw(rw);

			rw.setView(rw.getDefaultView());
			hud->draw(rw);
			if (paused)
				pauseMenu->draw(rw);
			rw.setView(v);
		}
	}

	void Game::buttonEvents(sf::RenderWindow& rw, sf::View& v) {
		if (!started) mainMenu->buttonEvents(rw, this);
		if (paused) pauseMenu->buttonEvents(rw, this);
	}

	void Game::controls(float timer) {
		if (started && !paused) {
#define keyPressed(key) sf::Keyboard::isKeyPressed(key)
#define key sf::Keyboard

			if (keyPressed(key::Escape)) pause(true);

			if (keyPressed(key::Up)) player->go(timer, Player::up);
			if (keyPressed(key::Down)) player->go(timer, Player::down);
			if (keyPressed(key::Left)) player->go(timer, Player::left);
			if (keyPressed(key::Right)) player->go(timer, Player::right);

			if (keyPressed(key::N)) {
				attributes->update(player);
			}

			if (keyPressed(key::Q)) player->stats.hp--;
			if (keyPressed(key::W)) player->stats.hp++;
			if (keyPressed(key::E)) player->stats.mp--;
			if (keyPressed(key::R)) player->stats.mp++;
			if (keyPressed(key::T)) player->stats.exp++;
			if (keyPressed(key::Y)) player->stats.lvl++;

#undef keyPressed
#undef key
		}
	}

	void Game::update(float timer, sf::View& v) {
		v.setCenter(player->getPosition());
		hud->update(player);
		player->update();
		controls(timer);
	}

	void Game::start(bool b) {
		started = b;
	}

	void Game::pause(bool b) {
		paused = b;
	}

	void Game::save() {
		// there's nothing to save yet
	}

	bool Game::load() {
		// there's nothing to load yet, so we can just lie that the load is succeeded
		return true;
	}

	bool Game::loadNewGame() {
		// there's nothing to load yet, so we can just lie that the load is succeeded
		return true;
	}

	bool Game::isStarted() {
		return started;
	}

	bool Game::isPaused() {
		return paused;
	}

}
