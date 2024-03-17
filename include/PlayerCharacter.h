#pragma once

#include <SFML/Graphics.hpp>

#include "DropExp.h"

class PlayerCharacter
{
	public:

		PlayerCharacter();

		void initTexture();
		void createSprite();

		sf::Texture pcTexture;
		sf::Sprite pcSprite;

		sf::Vector2f pcOffset{ -50.f, -50.f };

		float getPlayerSpeed() const { return m_playerSpeed; }

		float getPlayerHealth() const { return m_playerHealth; }

		float setPlayerHealth(float newHealth)
		{
			if(m_playerHealth == 0)
				return 0;
			else 
				return m_playerHealth = newHealth;
		}

		float getPlayerExp() const { return m_playerExp; }

		float setPlayerExp(float newXp)
		{
			return m_playerExp = newXp;
		}

	private:

		float m_playerSpeed { 0.5f };
		float m_playerHealth { 100.f };
		float m_playerExp { 0.f };
};
