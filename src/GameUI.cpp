#include "GameUI.h"

#include <iostream>

GameUI::GameUI()
{
	if (!font.loadFromFile("../assets/fonts/arial.ttf"))
	{
		// error...
	}
	else
	{
		std::cout << "UI Font Loaded" << std::endl;
		// select the font
		text.setFont(font); // font is a sf::Font
		// set the character size
		text.setCharacterSize(24); // in pixels, not points!
		// set the string to display
		text.setString(" ");
		// set the color
		text.setFillColor(sf::Color::Magenta);
		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		initPlayerHealthUI();
		initPLayerExperienceUI();
	}
}

void GameUI::initPlayerHealthUI()
{
	playerHP.setFont(font);
	playerHP.setCharacterSize(24);
	playerHP.setString(" ");
	playerHP.setFillColor(sf::Color ::Magenta);
	playerHP.setStyle((sf::Text::Bold | sf::Text::Underlined));
}

void GameUI::initPLayerExperienceUI()
{
	playerXP.setFont(font);
	playerXP.setCharacterSize(24);
	playerXP.setString(" ");
	playerXP.setFillColor(sf::Color ::Magenta);
	playerXP.setStyle((sf::Text::Bold | sf::Text::Underlined));
}

void GameUI::updateGameUI(PlayerCharacter* playerCharacter)
{
	// PlayerPosition
	text.setString(std::to_string((playerCharacter->pcSprite.getPosition().x)) + " , " + std::to_string((playerCharacter->pcSprite.getPosition().y)));
	text.setPosition(playerCharacter->pcSprite.getPosition().x + offsetUI.x, playerCharacter->pcSprite.getPosition().y + offsetUI.y);

	// PlayerHealth
	playerHP.setString("HP: " + std::to_string(std::int8_t(playerCharacter->getPlayerHealth())));
	playerHP.setPosition(playerCharacter->pcSprite.getPosition().x + offsetUI.x, playerCharacter->pcSprite.getPosition().y + offsetUI.y + 30.f);

	// PlayerExperience
	playerXP.setString("XP: " + std::to_string(std::int8_t(playerCharacter->getPlayerExp())));
	playerXP.setPosition(playerCharacter->pcSprite.getPosition().x + offsetUI.x, playerCharacter->pcSprite.getPosition().y + offsetUI.y + 60.f);
}

void GameUI::renderGameUI(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(text);
	gameWindow.draw(playerHP);
	gameWindow.draw(playerXP);
}
