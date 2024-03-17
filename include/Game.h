#pragma once

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "DropExp.h"
#include "EnemyCharacter.h"
#include "GameUI.h"
#include "ObjectPooler.h"
#include "PlayerCharacter.h"

class Game
{
	public:

		void initGame(sf::RenderWindow& gameWindow);
		void updateGame(sf::Int32 deltaTimeMs);
		void renderGame(sf::RenderWindow& gameWindow);

		ObjectPooler<EnemyCharacter> enemyCharacterPool;
		ObjectPooler<DropExp> dropXpPool;

	private:

		GameUI* m_gameUI;
		PlayerCharacter* m_playerCharacter = nullptr;
		Background* m_backgroundTile = nullptr;

		sf::View m_view;
		sf::Vector2f m_viewCenter;
		sf::Vector2f m_viewSize;
		sf::FloatRect m_currentViewRect;
};
