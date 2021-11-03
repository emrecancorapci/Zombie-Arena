#include "TextureHolder.h"
#include <cassert>

TextureHolder* TextureHolder::_instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(_instance == nullptr);
	_instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename)
{
	auto& m = _instance->_textures;

	auto keyValuePair = m.find(filename);

	if(keyValuePair != m.end())
	{
		return keyValuePair -> second;
	}
	else
	{
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}
