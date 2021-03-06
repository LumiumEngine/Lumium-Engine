#include "Font.hpp"
#include <fstream>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
#include <iostream>

lumi::graphics::Font::Font()
{
	m_fontInfo = FontInfo();
}

lumi::graphics::Font::~Font()
{
}

bool lumi::graphics::Font::loadFont(std::string fontFile)
{
	auto fontData = readFontFile(fontFile);
	if (fontData.empty())
		return false;
	auto atlasData = std::make_unique<uint8_t[]>(m_fontInfo.atlasWidth * m_fontInfo.atlasHeight);
	m_fontInfo.charInfo = std::make_unique<stbtt_packedchar[]>(m_fontInfo.charCount);

	/* load font file */
	long size;
	unsigned char* fontBuffer;
	FILE* fontFiles = fopen(fontFile.c_str(), "rb");
	fseek(fontFiles, 0, SEEK_END);
	size = ftell(fontFiles); /* how long is the file ? */
	fseek(fontFiles, 0, SEEK_SET); /* reset */

	fontBuffer = static_cast<unsigned char*>(malloc(size));

	fread(fontBuffer, size, 1, fontFiles);
	fclose(fontFiles);

	auto result = stbtt_InitFont(&m_font, fontBuffer, 0);

	stbtt_pack_context context;
	if (!stbtt_PackBegin(&context, atlasData.get(), m_fontInfo.atlasWidth, m_fontInfo.atlasHeight, 0, 1, nullptr))
		return false;

	stbtt_PackSetOversampling(&context, m_fontInfo.oversampleX, m_fontInfo.oversampleY);
	if (!stbtt_PackFontRange(&context, fontData.data(), 0, m_fontInfo.size, m_fontInfo.firstChar, m_fontInfo.charCount, m_fontInfo.charInfo.get()))
		return false;

	stbtt_PackEnd(&context);

	m_fontTexture.createFontTexture(m_fontInfo.atlasWidth, m_fontInfo.atlasHeight, atlasData.get());
	
	return true;
}

lumi::graphics::GlyphInfo lumi::graphics::Font::getGlyphInfo(uint32_t character, float xOffset, float yOffset)
{
	stbtt_aligned_quad quad;

	stbtt_GetPackedQuad(m_fontInfo.charInfo.get(), m_fontInfo.atlasWidth, m_fontInfo.atlasHeight,
		character - m_fontInfo.firstChar, &xOffset, &yOffset, &quad, 1);
	auto xmin = quad.x0;
	auto xmax = quad.x1;
	auto ymin = -quad.y1;
	auto ymax = -quad.y0;

	GlyphInfo info{};
	info.offsetX = xOffset;
	info.offsetY = yOffset;
	info.positions[0] = { xmin, ymin, 0 };
	info.positions[1] = { xmin, ymax, 0 };
	info.positions[2] = { xmax, ymax, 0 };
	info.positions[3] = { xmax, ymin, 0 };
	info.uvs[0] = { quad.s0, quad.t1 };
	info.uvs[1] = { quad.s0, quad.t0 };
	info.uvs[2] = { quad.s1, quad.t0 };
	info.uvs[3] = { quad.s1, quad.t1 };

	return info;
}

int lumi::graphics::Font::getVerticalPosition()
{
	int ascent, descent, lineGap;
	auto scale = stbtt_ScaleForPixelHeight(&m_font, m_fontInfo.size);
	stbtt_GetFontVMetrics(&m_font, &ascent, &descent, &lineGap);
	ascent *= scale;
	descent *= scale;
	lineGap *= scale;
	return static_cast<int>(ascent - descent + lineGap);
}

std::vector<uint8_t> lumi::graphics::Font::readFontFile(std::string fontFile)
{
	std::ifstream file(fontFile, std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return std::vector<uint8_t>();

	const auto size = file.tellg();
	file.seekg(0, std::ios::beg);
	auto bytes = std::vector<uint8_t>(size);
	file.read(reinterpret_cast<char*>(&bytes[0]), size);
	file.close();

	return bytes;
}