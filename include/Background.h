#pragma once

#include <SFML/Graphics.hpp>

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

		void InitTexture();
		void CreateSprite();

		sf::Texture bTexture0;
		sf::Texture bTexture1;
		sf::Texture bTexture2;
		sf::Texture bTexture3;
		sf::Texture bTexture4;
		sf::Sprite bSprite;

		void CreateBackground();
		void DrawBackground(sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect);
		bool IsInView(sf::Sprite& spriteAABB, sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect) const;

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