#pragma once

#include <SFML/Graphics.hpp>

#include "TextureLoader.h"

class BiomeInfo
{
public:
    int type = 0;
    int x = 0;
    int y = 0;
};

class Background
{
	public:

	    Background();

		void initTexture(TextureLoader* textureLoader);
		void createSprite();

		sf::Texture bTexture0;
		sf::Texture bTexture1;
		sf::Texture bTexture2;
		sf::Texture bTexture3;
		sf::Texture bTexture4;
		sf::Sprite bSprite;

		void createBackground();
		void drawBackground(sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect);
		bool isInView(sf::Sprite& spriteAABB, sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect) const;

		const static int columns{ 100 };
		const static int rows{ 100 };
		float backgroundOffset;

		sf::Sprite aSprites[columns][rows];
		BiomeInfo bgBiome[5];

	private:

		int m_biome {0};
		float m_tileScale{ 10.f };
		float m_tileSize{ 100.f };
};