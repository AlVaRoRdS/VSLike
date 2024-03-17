#include<iostream>
#include "Game.h"


void Game::initGame(sf::RenderWindow& gameWindow)
{
	// Creates the player character
	m_playerCharacter = new PlayerCharacter();
	// Creates the Background
	m_backgroundTile = new Background();
	// Creates the UI
	m_gameUI = new GameUI();

	// TODO Spawner -----------------------------
	for(int i = 0; i < 2; i++)
		enemyCharacterPool.get()->initEnemyCharacter();

	for(int i = 0; i < 10; i++)
		dropXpPool.get()->initDropExp();
	// TODO -------------------------------------

	// Reset View and assigns the center
	m_view.reset(sf::FloatRect(1920u, 1080u, 1920u, 1080u));
	m_view.setCenter(0.f, 0.f);

	// Set view
	gameWindow.setView(m_view);
}

void Game::updateGame(sf::Int32 deltaTimeMs)
{
	// Input Actions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_playerCharacter->pcSprite.move(- m_playerCharacter->getPlayerSpeed() * deltaTimeMs, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_playerCharacter->pcSprite.move(m_playerCharacter->getPlayerSpeed() * deltaTimeMs, 0.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_playerCharacter->pcSprite.move(0.f, - m_playerCharacter->getPlayerSpeed() * deltaTimeMs);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_playerCharacter->pcSprite.move(0.f, m_playerCharacter->getPlayerSpeed() * deltaTimeMs);
	
	// UpdateUI
	m_gameUI->updateGameUI(m_playerCharacter);

	// Update Enemy Position
	for(auto obj : enemyCharacterPool.getPooledObjects())
	{
		if(obj->isActive)
			obj->update(deltaTimeMs, m_playerCharacter);
		else
			enemyCharacterPool.put(obj);
	}

	// Update Experience Position
	for(auto obj : dropXpPool.getPooledObjects())
	{
		if(obj->isActive)
			obj->update(deltaTimeMs, m_playerCharacter);
		else
			dropXpPool.put(obj);
	}
}

void Game::renderGame(sf::RenderWindow& gameWindow)
{
	// Clear everything from the window before draw it again 
	gameWindow.clear();

	// Updates Camera to Player Position
	m_view.setCenter(m_playerCharacter->pcSprite.getPosition() - m_playerCharacter->pcOffset);
	gameWindow.setView(m_view);

	// Camera Rect for render background tiles
	m_viewCenter = m_view.getCenter();
	m_viewSize = m_view.getSize();
	m_currentViewRect = {m_viewCenter - m_viewSize / 2.f, m_viewSize};
	// Updates Background Tiles
	m_backgroundTile->DrawBackground(gameWindow, m_currentViewRect);

	// Renders Exp Position
	for (auto obj : dropXpPool.getPooledObjects())
	{
		if (obj->isActive)
			gameWindow.draw(obj->deSprite);
		else // If is not active anymore, return it to the pool
			dropXpPool.put(obj);
	}

	// Renders Player, Must be the last for be shown the First over the other sprites
	gameWindow.draw(m_playerCharacter->pcSprite);

	// Renders Enemy Position
	for (auto obj : enemyCharacterPool.getPooledObjects())
	{
		if (obj->isActive)
			gameWindow.draw(obj->ecSprite);
		else
			enemyCharacterPool.put(obj);
	}

	// Draw UI
	m_gameUI->renderGameUI(gameWindow);

	// Display
	gameWindow.display();
}
