#include "TextureLoader.h"

#include<iostream>


TextureLoader::TextureLoader()
{
	loadTextures();
}

void TextureLoader::loadTextures()
{
	std::cout << "//////// Loading Textures ////////" << std::endl;

	if (!tlTexture[0].loadFromFile("../assets/textures/character.png"))
		std::cout << "Error loading PlayerCharacter Image" << std::endl;
	else
		std::cout << "// PlayerCharacter Image Loaded //" << std::endl;

	if (!tlTexture[1].loadFromFile("../assets/textures/baseAttack.png"))
		std::cout << "Error loading BaseAttack Image" << std::endl;
	else
		std::cout << "// BaseAttack Image Loaded      //" << std::endl;

	if (!tlTexture[2].loadFromFile("../assets/textures/enemyCharacter.png"))
		std::cout << "Error loading EnemyCharacter Image" << std::endl;
	else
		std::cout << "// EnemyCharacter Image Loaded  //" << std::endl;

	if (!tlTexture[3].loadFromFile("../assets/textures/dropExp.png"))
		std::cout << "Error loading DropExp Image" << std::endl;
	else
		std::cout << "// DropExp Image Loaded         //" << std::endl;

	if (!tlTexture[4].loadFromFile("../assets/textures/backgroundTile0.png"))
		std::cout << "Error loading Background Image 0" << std::endl;
	else
		std::cout << "// Background Image 0 Loaded    //" << std::endl;

	if (!tlTexture[5].loadFromFile("../assets/textures/backgroundTile1.png"))
		std::cout << "Error loading Background Image 1" << std::endl;
	else
		std::cout << "// Background Image 1 Loaded    //" << std::endl;

	if (!tlTexture[6].loadFromFile("../assets/textures/backgroundTile2.png"))
		std::cout << "Error loading Background Image 2" << std::endl;
	else
		std::cout << "// Background Image 2 Loaded    //" << std::endl;

	if (!tlTexture[7].loadFromFile("../assets/textures/backgroundTile3.png"))
		std::cout << "Error loading Background Image 3" << std::endl;
	else
		std::cout << "// Background Image 2 Loaded    //" << std::endl;

	if (!tlTexture[8].loadFromFile("../assets/textures/backgroundTile4.png"))
		std::cout << "Error loading Background Image 4" << std::endl;
	else
		std::cout << "// Background Image 2 Loaded    //" << std::endl;

	std::cout << "//////////////////////////////////" << std::endl;
}
