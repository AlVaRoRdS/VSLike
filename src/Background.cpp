#include<iostream>
#include <SFML/Graphics.hpp>

#include "Background.h"

Background::Background()
{
	bgBiome[0].type = 0;
	bgBiome[0].x = 10;
	bgBiome[0].y = 10;

	bgBiome[1].type = 1;
	bgBiome[1].x = 60;
	bgBiome[1].y = 40;

	bgBiome[2].type = 2;
	bgBiome[2].x = 90;
	bgBiome[2].y = 90;

	bgBiome[3].type = 3;
	bgBiome[3].x = 90;
	bgBiome[3].y = 10;

	bgBiome[4].type = 4;
	bgBiome[4].x = 20;
	bgBiome[4].y = 75;

	InitTexture();
	CreateBackground();
}

void Background::InitTexture()
{
	// TODO Change to a single texture and cut it in different variables
	if (!bTexture0.loadFromFile("../assets/textures/backgroundTile0.png"))
		std::cout << "Error loading Background Image 0" << std::endl;
	else
		std::cout << "Background Image 0 Loaded" << std::endl;

	if (!bTexture1.loadFromFile("../assets/textures/backgroundTile1.png"))
		std::cout << "Error loading Background Image 1" << std::endl;
	else
		std::cout << "Background Image 1 Loaded" << std::endl;

	if (!bTexture2.loadFromFile("../assets/textures/backgroundTile2.png"))
		std::cout << "Error loading Background Image 2" << std::endl;
	else
		std::cout << "Background Image 2 Loaded" << std::endl;

	if (!bTexture3.loadFromFile("../assets/textures/backgroundTile3.png"))
		std::cout << "Error loading Background Image 3" << std::endl;
	else
		std::cout << "Background Image 2 Loaded" << std::endl;

	if (!bTexture4.loadFromFile("../assets/textures/backgroundTile4.png"))
		std::cout << "Error loading Background Image 4" << std::endl;
	else
		std::cout << "Background Image 2 Loaded" << std::endl;
}

void Background::CreateBackground()
{
	// Half of the size of the array so the center would be (0,0)
	backgroundOffset = (columns * m_tileScale * m_tileSize) / -2;

	// Instantiate the array tiles
	for(int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int nearest = 0;
            int dist = 10000;

            for (int z = 0; z < 5; z++) 
			{
                int xdiff = bgBiome[z].x - i;
                int ydiff = bgBiome[z].y - j;

                int cdist = xdiff*xdiff + ydiff*ydiff;

                if (cdist < dist)
				{
                    nearest = bgBiome[z].type;
                    dist = cdist;
                }
            }
            m_biome = nearest;

			switch(m_biome)
			{
				case 0:
					aSprites[i][j].setTexture(bTexture1);
					break;
				case 1:
					aSprites[i][j].setTexture(bTexture0);
					break;
				case 2:
					aSprites[i][j].setTexture(bTexture2);
					break;
				case 3:
					aSprites[i][j].setTexture(bTexture3);
					break;
				case 4:
					aSprites[i][j].setTexture(bTexture4);
					break;
			}
			aSprites[i][j].setScale(m_tileScale, m_tileScale);
			aSprites[i][j].setPosition(backgroundOffset + ((i + 1) * m_tileSize * m_tileScale), backgroundOffset + ((j + 1) * m_tileSize * m_tileScale));
		}
	}
}

void Background::DrawBackground(sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			// Checks if the tiles is viewed in the view
			if(IsInView(aSprites[i][j], gameWindow, currentViewRect))
			{
				gameWindow.draw(aSprites[i][j]);
				// Debug for Tile Drew
				//std::cout << "| " << i << "," << j << " |";
			}
		}
	}
	//std::cout << std::endl;
}

bool Background::IsInView(sf::Sprite& sprite, sf::RenderWindow& gameWindow, sf::FloatRect& currentViewRect) const 
{
	sf::FloatRect rect;
	rect.left = sprite.getPosition().x;
	rect.top = sprite.getPosition().y;
	rect.width = m_tileSize * m_tileScale;
	rect.height = m_tileSize * m_tileScale;

	return rect.intersects(currentViewRect);
}