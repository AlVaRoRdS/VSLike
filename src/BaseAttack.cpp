#include "BaseAttack.h"

#include<iostream>

#include "PlayerCharacter.h"

BaseAttack::BaseAttack()
{
	initBaseAttack();
}

void BaseAttack::initBaseAttack()
{
	isActive = true;
	baDirection = (rand() % 2);
	if (baDirection == 0)
		baDirection = -1;
}

void BaseAttack::initTexture(sf::Texture& loadedTexture)
{
	baTexture = loadedTexture;
	baSprite.setTexture(baTexture);
}

void BaseAttack::createSprite(const float& xPos, const float& yPos)
{
	baSprite.setPosition(xPos, yPos);
	baSprite.setScale(m_baseAttackScale.x, m_baseAttackScale.y);
}

void BaseAttack::update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter)
{
	if(isActive)
	{
		baSprite.setPosition(baSprite.getPosition().x + (10 * deltaTimeMs * m_baseAttackSpeed * baDirection),
								baSprite.getPosition().y);

		if(m_bulletCoolDown >= 600.f)
		{
			m_bulletCoolDown = 0.f;
			isActive = false;
		}
		else
			m_bulletCoolDown += (m_cooldownRatio * deltaTimeMs);
	}
}