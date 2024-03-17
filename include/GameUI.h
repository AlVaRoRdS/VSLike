#pragma once
#include "PlayerCharacter.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class GameUI
{
	public:
		GameUI();
		sf::Font font;
		sf::Text text;
		sf::Text playerHP;
		sf::Text playerXP;
		sf::Vector2f offsetUI {- 850,- 450};

		void initPlayerHealthUI();
		void initPLayerExperienceUI();

		void updateGameUI(PlayerCharacter* playerCharacter);
		void renderGameUI(sf::RenderWindow& gameWindow);
};
