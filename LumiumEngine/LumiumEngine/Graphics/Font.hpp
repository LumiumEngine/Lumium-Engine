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

		struct FontInfo
		{
			FontInfo()
			{
				size = 20;
				atlasWidth = 2048;
				atlasHeight = 2048;
				oversampleX = 8;
				oversampleY = 8
					;
				firstChar = ' ';
				charCount = '~' - ' ';
				charInfo.reset();
			};
			uint32_t size;
			uint32_t atlasWidth ;
			uint32_t atlasHeight;
			uint32_t oversampleX;
			uint32_t oversampleY;
			uint32_t firstChar;
			uint32_t charCount;
			std::unique_ptr<stbtt_packedchar[]> charInfo;
		};

		class Font
		{
		public:
			Font();
			~Font();
			bool loadFont(std::string fontFile);
			GlyphInfo getGlyphInfo(uint32_t character, float xOffset, float yOffset);
			lumi::graphics::Texture& getTexture() { return m_fontTexture; }
			int getVerticalPosition();
		private:
			stbtt_fontinfo m_font;
			std::vector<uint8_t> readFontFile(std::string fontFile);
			FontInfo m_fontInfo;
			lumi::graphics::Texture m_fontTexture;
		};
	}
};