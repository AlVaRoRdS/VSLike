#include<iostream>

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	createSprite();
}

void PlayerCharacter::initTexture(sf::Texture& loadedTexture)
{
	pcTexture = loadedTexture;
	pcSprite.setTexture(pcTexture);
}

void PlayerCharacter::createSprite()
{
	// Assigns the offset so the pivot would look more in the center of the sprite
	pcSprite.setPosition(-50.f, -50.f);
}