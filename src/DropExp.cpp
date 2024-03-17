#include "DropExp.h"

#include <iostream>

#include "PlayerCharacter.h"

DropExp::DropExp()
{
	initDropExp();
}

void DropExp::initDropExp()
{
	initTexture();
	createSprite();
}

void DropExp::initTexture()
{
	if (!deTexture.loadFromFile("../assets/textures/dropExp.png"))
	{
		std::cout << "Error loading DropExp Image" << std::endl;
	}
	else
	{
		std::cout << "DropExp Image Loaded" << std::endl;
	}
}

void DropExp::createSprite()
{
	deSprite.setTexture(deTexture);
	deSprite.setScale(m_deScale, m_deScale);
	deSprite.setPosition(400.f, 400.f);
	
}

void DropExp::update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter)
{
	if(isActive)
	{
		sf::Vector2f vectorDirection {playerCharacter->pcSprite.getPosition().x - (deSprite.getPosition().x + m_deOffset.x),
										playerCharacter->pcSprite.getPosition().y - (deSprite.getPosition().y + m_deOffset.y)};

		float distance = std::sqrt(vectorDirection.x * vectorDirection.x + vectorDirection.y * vectorDirection.y);

		if(distance != 0)
			vectorDirection /= distance;

		// Chase the player
		if(distance <= m_dropExpRange || m_chase)
		{
			m_chase = true;
			deSprite.setPosition(deSprite.getPosition().x + (vectorDirection.x * deltaTimeMs * m_dropExpSpeed) ,
								deSprite.getPosition().y + (vectorDirection.y * deltaTimeMs * m_dropExpSpeed));
		}

		// Checks if interescts
		if(deSprite.getGlobalBounds().intersects(playerCharacter->pcSprite.getGlobalBounds()))
		{
			// Adds Experience to the player
			playerCharacter->setPlayerExp(playerCharacter->getPlayerExp() + m_dropExpValue);
			// Sets innactive for get pooled back to the pool
			isActive = false;
		}
	}
}