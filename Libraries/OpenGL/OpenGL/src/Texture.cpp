#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependency/stb_image.h"
#include <GL/glew.h>
Texture::Texture(std::string_view filepath)
{
	stbi_convert_iphone_png_to_rgb(1);
	buffer = std::unique_ptr<unsigned char>{ static_cast<unsigned char*>(stbi_load(filepath.data(), &width, &height, &bits_per_pixel, 4)) };

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());

}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
