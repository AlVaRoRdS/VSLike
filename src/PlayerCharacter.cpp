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
	pcSprite.setPosition(-50.f, -50.f);
}