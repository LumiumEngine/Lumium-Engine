#include "Texture.hpp"
#define STBI_ONLY_PNG // we only want to support PNG files
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

lumi::graphics::TextureParms::TextureParms()
{
	minFilter = std::make_pair(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	maxFilter = std::make_pair(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	minLOD = std::make_pair(GL_TEXTURE_MIN_LOD, -1000.0f);
	maxLOD = std::make_pair(GL_TEXTURE_MAX_LOD, 1000.0f);
	maxLevel = std::make_pair(GL_TEXTURE_MAX_LEVEL, 1000);
	wrap = std::make_pair(glm::ivec3(GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R), glm::ivec3(GL_CLAMP_TO_BORDER));
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
	stbi_set_flip_vertically_on_load(1);
	unsigned char * imageData = stbi_load(fileName.c_str(), &width, &height, &n, 4);
	glTextureStorage2D(m_textureID, 1, GL_RGBA8, width, height);
	glTextureSubImage2D(m_textureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
	glGenerateTextureMipmap(m_textureID);
}

void lumi::graphics::Texture::createFontTexture(int width, int height, uint8_t* data, TextureType type, TextureParms texParms)
{
	m_textureType = type;
	glCreateTextures(static_cast<GLenum>(type), 1, &m_textureID);
	texParms.updateParms(m_textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureStorage2D(m_textureID, 1, GL_RGB4, width, height);
	glTextureSubImage2D(m_textureID, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, data);
	glGenerateTextureMipmap(m_textureID);
}

int lumi::graphics::Texture::createTextureArray(std::string fileName, int width, int height, TextureParms texParms)
{
	m_textureType = TextureType::Tx2DArray;
	glCreateTextures(static_cast<GLenum>(m_textureType), 1, &m_textureID);
	texParms.updateParms(m_textureID);

	GLint imageWidth, imageHeight, n;
	GLint depth, levels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char * imageData = stbi_load(fileName.c_str(), &imageWidth, &imageHeight, &n, 4);
	depth = (imageWidth / width) * (imageHeight / height);
	levels = depth - 1;

	glTextureStorage3D(m_textureID, levels, GL_RGBA8, 128, 128, depth);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, imageWidth);
	for (int i = 0; i < depth; ++i)
	{
		const int xOff = (i % 2) * width;
		const int yOff = (i / 2 | 0) * height;
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, xOff);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, yOff);
		const int level = 0;
		glTextureSubImage3D(m_textureID, level, 0, 0, i, 128, 128, 1, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	glGenerateTextureMipmap(m_textureID);

	stbi_image_free(imageData);
	return depth;
}

void lumi::graphics::Texture::bindTexture(GLuint activeTexture)
{
	glBindTextureUnit(activeTexture, m_textureID);
}

void lumi::graphics::Texture::unbindTexture()
{
	glBindTexture(static_cast<GLenum>(m_textureType), 0);
}