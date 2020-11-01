#pragma once
#include <memory>
#include <string_view>
class Texture
{
	unsigned int id=0;
	std::unique_ptr<unsigned char> buffer;
	int width=0;
	int height=0;
	int bits_per_pixel = 0;
public:
	Texture(std::string_view filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

};

