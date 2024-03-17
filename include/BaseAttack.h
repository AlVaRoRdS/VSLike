#pragma once

#include <SFML/Graphics.hpp>

#include "DropExp.h"

class BaseAttack
{
	public:

		BaseAttack();

		void initBaseAttack();

		void initTexture(sf::Texture& loadedTexture);
		void createSprite(const float& xPos,const float& yPos);

		sf::Texture baTexture;
		sf::Sprite baSprite;

		sf::Vector2f baOffset{ -50.f, -50.f };

		float getBaseAttackSpeed() const { return m_baseAttackSpeed; }
		float getBaseAttackDamage() const { return m_baseAttackDamage; }

		void update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter);

		bool isActive { true };
		int baDirection { 1 };

	private:

		sf::Vector2f m_baseAttackScale{ 1.f, 0.3f};
		float m_baseAttackSpeed { 0.2f };
		float m_baseAttackDamage { 10.f };
		float m_cooldownRatio { 1.f };
		float m_bulletCoolDown { 0.f };
		bool m_canDoDamage { true };
};
