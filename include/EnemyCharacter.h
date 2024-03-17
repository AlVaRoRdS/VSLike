#pragma once

#include <SFML/Graphics.hpp>

#include "ObjectPooler.h"
#include "BaseAttack.h"

#include "PlayerCharacter.h"


class EnemyCharacter
{
	public:

		EnemyCharacter();

		void initEnemyCharacter();

		void initTexture(sf::Texture& loadedTexture);
		void createSprite(const float& xPos,const float& yPos);

		sf::Texture ecTexture;
		sf::Sprite ecSprite;

		sf::Vector2f ecOffset{ -50.f, -50.f };

		float getEnemySpeed() const { return m_enemySpeed; }
		float getEnemyHealth() const { return m_enemyHealth; }
		float setEnemyHealth(float newHealth)
		{
			m_enemyHealth = newHealth;
			return m_enemyHealth;
		}

		void update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter, std::list<BaseAttack*> pooledBaseAttack);
		bool isInView(sf::FloatRect& currentViewRect) const;

		bool isActive { true };

	private:

		float m_enemySize { 100.f };
		float m_enemyScale { 1.f };
		float m_enemyHealth { 30.f };
		float m_enemySpeed { 0.2f };
		float m_enemyDamage { 1.f };
		float m_damageRatio { 10.f };
		float m_damageCurrentRatio { 0.f };
		float m_damageCoolDown { 1000.f };
		bool m_canDoDamage { true };
		
};
