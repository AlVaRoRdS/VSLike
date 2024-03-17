#include<iostream>

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	initTexture();
	createSprite();
}

void PlayerCharacter::initTexture()
{
	if (!pcTexture.loadFromFile("../assets/textures/character.png"))
	{
		std::cout << "Error loading PlayerCharacter Image" << std::endl;
	}
	else
	{
		std::cout << "PlayerCharacter Image Loaded" << std::endl;
	}
}

void PlayerCharacter::createSprite()
{
	pcSprite.setTexture(pcTexture);
	pcSprite.setPosition(-50.f, -50.f);
}