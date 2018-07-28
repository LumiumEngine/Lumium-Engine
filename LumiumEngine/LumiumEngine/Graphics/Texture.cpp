#include "Texture.hpp"
#define STBI_ONLY_PNG // we only want to support PNG files
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

lumi::graphics::TextureParms::TextureParms()
{
	minFilter = std::make_pair(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	maxFilter = std::make_pair(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	minLOD = std::make_pair(GL_TEXTURE_MIN_LOD, -1000);
	maxLOD = std::make_pair(GL_TEXTURE_MAX_LOD, 1000);
	maxLevel = std::make_pair(GL_TEXTURE_MAX_LEVEL, 1000);
	wrap = std::make_pair(glm::ivec3(GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R), glm::ivec3(GL_REPEAT));
}

lumi::graphics::TextureParms::TextureParms(GLint pMinFilter, GLint pMaxFilter, GLfloat pMinLOD, GLfloat pMaxLOD, GLint pMaxLevel, glm::ivec3 pWrap)
{
	minFilter = std::make_pair(GL_TEXTURE_MIN_FILTER, pMinFilter);
	maxFilter = std::make_pair(GL_TEXTURE_MAG_FILTER, pMaxFilter);
	minLOD = std::make_pair(GL_TEXTURE_MIN_LOD, pMinLOD);
	maxLOD = std::make_pair(GL_TEXTURE_MAX_LOD, pMaxLOD);
	maxLevel = std::make_pair(GL_TEXTURE_MAX_LEVEL, pMaxLevel);
	wrap = std::make_pair(glm::ivec3(GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R), pWrap);
}

void lumi::graphics::TextureParms::updateParms(GLuint textureID)
{
	glTextureParameteri(textureID, minFilter.first, minFilter.second);
	glTextureParameteri(textureID, maxFilter.first, maxFilter.second);
	glTextureParameterf(textureID, minLOD.first, minLOD.second);
	glTextureParameterf(textureID, maxLOD.first, maxLOD.second);
	glTextureParameteri(textureID, maxLevel.first, maxLevel.second);
	glTextureParameteri(textureID, wrap.first.x, wrap.second.x);
	glTextureParameteri(textureID, wrap.first.y, wrap.second.y);
	glTextureParameteri(textureID, wrap.first.z, wrap.second.z);
}


lumi::graphics::Texture::Texture()
{
}

lumi::graphics::Texture::~Texture()
{
}

void lumi::graphics::Texture::createTexture(std::string fileName, TextureType type, TextureParms texParms)
{
	m_textureType = type;
	glCreateTextures(static_cast<GLenum>(type), 1, &m_textureID);
	texParms.updateParms(m_textureID);

	int width, height, n;
	if (type == TextureType::Tx2D)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char * imageData = stbi_load(fileName.c_str(), &width, &height, &n, 4);
		glTextureStorage2D(m_textureID, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(m_textureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
		glGenerateTextureMipmap(m_textureID);
	}
}

void lumi::graphics::Texture::bindTexture(GLuint activeTexture)
{
	glBindTextureUnit(activeTexture, m_textureID);
}

void lumi::graphics::Texture::unbindTexture()
{
	glBindTexture(static_cast<GLenum>(m_textureType), 0);
}