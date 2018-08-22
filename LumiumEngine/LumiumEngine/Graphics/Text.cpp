#include "Text.hpp"

lumi::graphics::Text::Text()
{
}

lumi::graphics::Text::~Text()
{
}

void lumi::graphics::Text::setFont(std::shared_ptr<lumi::graphics::Font> font)
{
    m_font = font;
}

void lumi::graphics::Text::createText(std::string text)
{
    lumi::graphics::Vertex vertex;

    GLushort lastIndex = 0;
    float offsetX = 0, offsetY = 0;
    for (auto c : text)
    {
        const auto glyphInfo = m_font->getGlyphInfo(c, offsetX, offsetY);
        offsetX = glyphInfo.offsetX;
        offsetY = glyphInfo.offsetY;

        for(int i =  0; i < 4; i++)
        {
            vertex.Position = glyphInfo.positions[i];
            vertex.TexCoord = glyphInfo.uvs[i];
            vertex.Normal = glm::vec3(0, 0, -1);
            m_vertices.push_back(vertex);
        }

        m_indices.push_back(lastIndex);
        m_indices.push_back(lastIndex + 1);
        m_indices.push_back(lastIndex + 2);
        m_indices.push_back(lastIndex);
        m_indices.push_back(lastIndex + 2);
        m_indices.push_back(lastIndex + 3);

        lastIndex += 4;
    }
}