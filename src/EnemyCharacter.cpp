#include<iostream>

#include "EnemyCharacter.h"

#include "Game.h"

EnemyCharacter::EnemyCharacter()
{
	//initEnemyCharacter();
}

void EnemyCharacter::initEnemyCharacter()
{
	isActive = true;
	m_enemyHealth = 500.f;
}

void EnemyCharacter::initTexture(sf::Texture& loadedTexture)
{
	ecTexture = loadedTexture;
	ecSprite.setTexture(ecTexture);
}

void EnemyCharacter::createSprite(const float& xPos,const float& yPos)
{
	ecSprite.setPosition(xPos, yPos);
}

void EnemyCharacter::update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter, std::list<BaseAttack*> pooledBaseAttack)
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

		// Checks if it intersects with Base Attack
		for( auto obj : pooledBaseAttack)
			if(ecSprite.getGlobalBounds().intersects(obj->baSprite.getGlobalBounds()))
				m_enemyHealth -= obj->getBaseAttackDamage();
	}
}

bool EnemyCharacter::isInView(sf::FloatRect& currentViewRect) const 
{
	sf::FloatRect rect;
	rect.left = ecSprite.getPosition().x;
	rect.top = ecSprite.getPosition().y;
	rect.width = m_enemySize * m_enemyScale;
	rect.height = m_enemySize * m_enemyScale;

	return rect.intersects(currentViewRect);
}