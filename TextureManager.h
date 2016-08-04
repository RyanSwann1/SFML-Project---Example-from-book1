#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "ResourceManager.h"
#include <SFML\Graphics\Texture.hpp>
#include <iostream>
class TextureManager : 
	public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager() : ResourceManager("Textures.cfg") {}
	~TextureManager() override {}

	sf::Texture* load(const std::string filePath)
	{
		sf::Texture* texture = new sf::Texture();
		//If failed to load texture
		if (!texture->loadFromFile(Utils::GetWorkingDirectory() + filePath))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "Failed to load texture " << filePath << "\n";
		}
		return texture;
	}
};
#endif // !TEXTURE_MANAGER_H
//
//
//#pragma once
//#include "ResourceManager.h"
//#include <SFML/Graphics/Texture.hpp>
//
//class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
//public:
//	TextureManager() : ResourceManager("textures.cfg") {}
//
//	sf::Texture* Load(const std::string& l_path) {
//		sf::Texture* texture = new sf::Texture();
//		if (!texture->loadFromFile(
//			Utils::GetWorkingDirectory() + l_path))
//		{
//			delete texture;
//			texture = nullptr;
//			std::cerr << "! Failed to load texture: " << l_path << std::endl;
//		}
//		return texture;
//	}
//};