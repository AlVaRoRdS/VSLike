#include<iostream>

#include "EnemyCharacter.h"

#include "Game.h"
#include "PlayerCharacter.h"

EnemyCharacter::EnemyCharacter()
{
	initEnemyCharacter();
}

void EnemyCharacter::initEnemyCharacter()
{
	initTexture();
	createSprite();
}

void EnemyCharacter::initTexture()
{
	if (!ecTexture.loadFromFile("../assets/textures/enemyCharacter.png"))
	{
		std::cout << "Error loading EnemyCharacter Image" << std::endl;
	}
	else
	{
		std::cout << "EnemyCharacter Image Loaded" << std::endl;
	}
}

void EnemyCharacter::createSprite()
{
	ecSprite.setTexture(ecTexture);
	ecSprite.setPosition(-400.f, -400.f);
}

void EnemyCharacter::update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter)
{
	if(isActive)
	{
		sf::Vector2f vectorDirection {playerCharacter->pcSprite.getPosition().x - ecSprite.getPosition().x, playerCharacter->pcSprite.getPosition().y - ecSprite.getPosition().y};

		float distance = std::sqrt(vectorDirection.x * vectorDirection.x + vectorDirection.y * vectorDirection.y);

		if(distance != 0)
			vectorDirection /= distance;

		ecSprite.setPosition(ecSprite.getPosition().x + (vectorDirection.x * deltaTimeMs * m_enemySpeed),
								ecSprite.getPosition().y + (vectorDirection.y * deltaTimeMs * m_enemySpeed));

		// Checks if intersects with Player
		if(ecSprite.getGlobalBounds().intersects(playerCharacter->pcSprite.getGlobalBounds()))
		{
			// Damage
			if(m_canDoDamage)
			{
				m_canDoDamage = false;
				playerCharacter->setPlayerHealth(playerCharacter->getPlayerHealth() - m_enemyDamage);
			}
			else
			{
				m_damageCurrentRatio = (m_damageRatio * deltaTimeMs) + m_damageCurrentRatio;
				if(m_damageCurrentRatio >= m_damageCoolDown)
				{
					m_canDoDamage = true;
					m_damageCurrentRatio = 0.f;
				}
			}
		}
		else
		{
			// If it doesn't intersect, resets for being able to do damage
			m_canDoDamage = true;
			m_damageCurrentRatio = 0.f;
		}

		// TODO Checks if intersects with Bullets

		
	}
}