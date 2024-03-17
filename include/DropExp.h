#pragma once

#include <SFML/Graphics.hpp>


class PlayerCharacter;

class DropExp
{
	public:

		DropExp();

		void initDropExp();

		void initTexture();
		void createSprite();

		sf::Texture deTexture;
		sf::Sprite deSprite;

		void update(sf::Int32& deltaTimeMs, PlayerCharacter* playerCharacter);

		bool isActive { true };

	private:

		bool m_chase {false};
		float m_deScale { 0.5f };
		sf::Vector2f m_deOffset{ -50.f * m_deScale, -50.f * m_deScale};
		float m_dropExpSpeed { 0.6f };
		float m_dropExpRange { 400.f };
		float m_dropExpValue { 10.f };
};
