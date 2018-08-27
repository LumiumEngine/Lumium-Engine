#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utility>
#include <string>

namespace lumi
{
	namespace graphics
	{
		enum class TextureType : unsigned int {Tx2D = GL_TEXTURE_2D, Tx2DArray = GL_TEXTURE_2D_ARRAY, Tx3D = GL_TEXTURE_3D, TxCubeMap = GL_TEXTURE_CUBE_MAP};
		struct TextureParms
		{
		public:
			TextureParms();
			TextureParms(GLint pMinFilter, GLint pMaxFilter, GLfloat pMinLOD, GLfloat pMaxLOD, GLint pMaxLevel, glm::ivec3 pWrap);
			// set all the parms from their needed calls]
			void updateParms(GLuint textureID);
		private:
			std::pair<GLenum, GLint> minFilter;
			std::pair<GLenum, GLint> maxFilter;
			std::pair<GLenum, GLfloat> minLOD;
			std::pair<GLenum, GLfloat> maxLOD;
			std::pair<GLenum, GLint> maxLevel;
			std::pair<glm::ivec3, glm::ivec3> wrap;
		};
		class Texture
		{
		public:
			Texture();
			~Texture();

			void createTexture(std::string fileName, TextureType type = TextureType::Tx2D, TextureParms texParms = TextureParms());
			void createFontTexture(int width, int height, uint8_t* data, TextureType type = TextureType::Tx2D, TextureParms texParms = TextureParms());
			// create texture array returns the total count of images added the texture array
			int createTextureArray(std::string fileName, int width, int height, TextureParms texParms = TextureParms());
			void bindTexture(GLuint activeTexture = 0);
			void unbindTexture();
		private:
			GLuint m_textureID;
			TextureType m_textureType;
		};
	}
};