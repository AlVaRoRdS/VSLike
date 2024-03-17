#include<iostream>
#include "Game.h"


void Game::initGame(sf::RenderWindow& gameWindow)
{
	// Load the Game Textures
	m_textureLoader = new TextureLoader;

	// Creates the player character
	m_playerCharacter = new PlayerCharacter();
	m_playerCharacter->initTexture(m_textureLoader->tlTexture[0]);

	// Creates the Background
	m_backgroundTile = new Background();
	m_backgroundTile->initTexture(m_textureLoader);
	m_backgroundTile->createBackground();

	// Creates the UI
	m_gameUI = new GameUI();

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

	// Base Attack Spawner
	if(m_baseAttackCooldown >= 200.f)
	{
		m_baseAttackCooldown = 0.f;
		BaseAttack* baPooledObject = baseAttackPool.get();
		baPooledObject->initBaseAttack();
		baPooledObject->initTexture(m_textureLoader->tlTexture[1]);
		baPooledObject->createSprite(m_playerCharacter->pcSprite.getPosition().x, m_playerCharacter->pcSprite.getPosition().y);
	}
	else
		m_baseAttackCooldown += (0.5f * deltaTimeMs);

	// Update BaseAttack Position
	for(auto obj : baseAttackPool.getPooledObjects())
	{
		if(obj->isActive)
			obj->update(deltaTimeMs, m_playerCharacter);
		else
			baseAttackPool.put(obj);
	}

	// Enemy Character Spawner
	if(m_enemySpawnCurrentCooldown >= m_enemySpawnCooldown)
	{
		m_enemySpawnCurrentCooldown = 0;
		m_enemySpawnCooldown -= 0.2f;

		// Select the spawn point depending on the quadrant
		float randomX { 0.f };
		float randomY { 0.f };
		int randomHeight = rand() / ((RAND_MAX) / 1920);
		int randomWidth = rand() / ((RAND_MAX) / 1080);
		switch(rand() % 4)
		{
			case 0:
				randomX = m_currentViewRect.left + randomHeight;
				randomY = m_currentViewRect.top - 300;
				break;
			case 1:
				randomX = m_currentViewRect.left + 1920 + 300;
				randomY = m_currentViewRect.top + randomWidth;
				break;
			case 2:
				randomX = m_currentViewRect.left + randomHeight;
				randomY = m_currentViewRect.top + 1080 + 300;
				break;
			case 3:
				randomX = m_currentViewRect.left - 300;
				randomY = m_currentViewRect.top + randomWidth;
				break;
		}

		EnemyCharacter* enemyRand = enemyCharacterPool.get();
		enemyRand->initEnemyCharacter();
		enemyRand->initTexture(m_textureLoader->tlTexture[2]);
		enemyRand->createSprite(randomX, randomY);
		enemyRand->setEnemyHealth(enemyRand->getEnemyHealth() + 0.1f);
	}
	else
		m_enemySpawnCurrentCooldown += (0.5f * deltaTimeMs);

	// Update Enemy Position
	for(auto obj : enemyCharacterPool.getPooledObjects())
	{
		if(obj->isActive)
		{
			obj->update(deltaTimeMs, m_playerCharacter, baseAttackPool.getPooledObjects());

			if(obj->getEnemyHealth() <= 0.f)
			{
				obj->isActive = false;
				// Spawns DropXp at location
				DropExp* drop = dropXpPool.get();
				drop->initDropExp();
				drop->initTexture(m_textureLoader->tlTexture[3]);
				drop->createSprite(obj->ecSprite.getPosition().x, obj->ecSprite.getPosition().y);
				enemyCharacterPool.put(obj);
			}
		}
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

	// Camera Rect
	m_viewCenter = m_view.getCenter();
	m_viewSize = m_view.getSize();
	m_currentViewRect = {m_viewCenter - m_viewSize / 2.f, m_viewSize};

	// Renders Background Tiles
	m_backgroundTile->drawBackground(gameWindow, m_currentViewRect);

	// Renders Exp Position
	for (auto obj : dropXpPool.getPooledObjects())
	{
		if (obj->isActive)
		{
			// Renders if is in view
			if(obj->isInView(m_currentViewRect))
				gameWindow.draw(obj->deSprite);
		}
		else // If is not active anymore, return it to the pool
			dropXpPool.put(obj);
	}

	// Renders PlayerCharacter
	gameWindow.draw(m_playerCharacter->pcSprite);

	// Renders Enemy Position
	for (auto obj : enemyCharacterPool.getPooledObjects())
	{
		if (obj->isActive)
		{
			// Renders if is in view
			if(obj->isInView(m_currentViewRect))
				gameWindow.draw(obj->ecSprite);
		}
		else
			enemyCharacterPool.put(obj);
	}

	// Renders BaseAttack Position
	for (auto obj : baseAttackPool.getPooledObjects())
	{
		if (obj->isActive)
			gameWindow.draw(obj->baSprite);
		else // If is not active anymore, return it to the pool
			baseAttackPool.put(obj);
	}

	// Draw UI
	m_gameUI->renderGameUI(gameWindow);

	// Display
	gameWindow.display();
}
