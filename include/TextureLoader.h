#pragma once

#include <SFML/Graphics.hpp>


class TextureLoader
{
	public:

		TextureLoader();

		void loadTextures();

		sf::Texture tlTexture[9];
};
