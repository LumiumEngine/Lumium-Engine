#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <stb/stb_truetype.h>
#include <LumiumEngine/Graphics/Texture.hpp>

namespace lumi
{
	namespace graphics
	{
		struct GlyphInfo
		{
			glm::vec3 positions[4];
			glm::vec2 uvs[4];
			float offsetX = 0;
			float offsetY = 0;
		};

		struct
		{
			const uint32_t size = 40;
			const uint32_t atlasWidth = 512;
			const uint32_t atlasHeight = 512;
			const uint32_t oversampleX = 2;
			const uint32_t oversampleY = 2;
			const uint32_t firstChar = ' ';
			const uint32_t charCount = '~' - ' ';
			std::unique_ptr<stbtt_packedchar[]> charInfo;
		    GLuint texture;
		} FontInfo;

		class Font
		{
		public:
			Font();
			~Font();
			bool loadFont(std::string fontFile);
			GlyphInfo getGlyphInfo(uint32_t character, float xOffset, float yOffset);
		private:
			std::vector<uint8_t> readFontFile(std::string fontFile);
		};
	}
};