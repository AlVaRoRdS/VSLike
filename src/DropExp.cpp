#include "DropExp.h"

#include <iostream>

#include "PlayerCharacter.h"

DropExp::DropExp()
{
	initDropExp();
}

void DropExp::initDropExp()
{
	isActive = true;
	m_chase = false;
}

void DropExp::initTexture(sf::Texture& loadedTexture)
{
	deTexture = loadedTexture;
	deSprite.setTexture(deTexture);
}

void DropExp::createSprite(const float& xPos,const float& yPos)
{
	deSprite.setScale(m_deScale, m_deScale);
	deSprite.setRotation(45);
	deSprite.setPosition(xPos, yPos);
}

void DropExp::update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter)
{
	if(isActive)
	{
		// Gets Player Position for determine direction
		sf::Vector2f vectorDirection {playerCharacter->pcSprite.getPosition().x - (deSprite.getPosition().x + m_deOffset.x),
										playerCharacter->pcSprite.getPosition().y - (deSprite.getPosition().y + m_deOffset.y)};

		float distance = std::sqrt(vectorDirection.x * vectorDirection.x + vectorDirection.y * vectorDirection.y);

		if(distance != 0)
			vectorDirection /= distance;

		// Chases the player
		if(distance <= m_dropExpRange || m_chase)
		{
			m_chase = true;
			deSprite.setPosition(deSprite.getPosition().x + (vectorDirection.x * deltaTimeMs * m_dropExpSpeed) ,
								deSprite.getPosition().y + (vectorDirection.y * deltaTimeMs * m_dropExpSpeed));
		}

		// Checks if interescts
		if(deSprite.getGlobalBounds().intersects(playerCharacter->pcSprite.getGlobalBounds()))
		{
			// Adds Experience to the Player Character
			playerCharacter->addPlayerExp(m_dropExpValue);
			// Sets innactive for get pooled back to the pool
			isActive = false;
		}
	}
}

bool DropExp::isInView(sf::FloatRect& currentViewRect) const 
{
	// Gets sprite rect
	sf::FloatRect rect;
	rect.left = deSprite.getPosition().x;
	rect.top = deSprite.getPosition().y;
	rect.width = m_deSize * m_deScale;
	rect.height = m_deSize * m_deScale;

	// Checks if intersects with the current view
	return rect.intersects(currentViewRect);
}