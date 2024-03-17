#pragma once

#include <SFML/Graphics.hpp>

#include "PlayerCharacter.h"

class EnemyCharacter
{
	public:

		EnemyCharacter();

		void initEnemyCharacter();

		void initTexture();
		void createSprite();

		sf::Texture ecTexture;
		sf::Sprite ecSprite;

		sf::Vector2f ecOffset{ -50.f, -50.f };

		float getEnemySpeed() const { return m_enemySpeed; }

		void update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter);

		bool isActive { true };

	private:

		float enemyHealth { 10.f };
		float m_enemySpeed { 0.2f };
		float m_enemyDamage { 1.f };
		float m_damageRatio { 10.f };
		float m_damageCurrentRatio { 0.f };
		float m_damageCoolDown { 1000.f };
		bool m_canDoDamage { true };
		
};
