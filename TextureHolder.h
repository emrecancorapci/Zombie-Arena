#pragma once

#ifndef TEXTURE_HOLDER_H

#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;


class TextureHolder
{
private:
	map <string, Texture> _textures;
	static TextureHolder* _instance;

public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);
};

#endif
