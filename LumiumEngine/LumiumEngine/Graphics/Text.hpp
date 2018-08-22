#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <LumiumEngine/Graphics/Drawable.hpp>
#include <LumiumEngine/Graphics/Font.hpp>

namespace lumi
{
	namespace graphics
	{
		class Text : public Drawable
		{
		public:
		    Text();
		    ~Text();
		    void setFont(std::shared_ptr<lumi::graphics::Font> font);
		    void createText(std::string text);
		private:
		    std::shared_ptr<lumi::graphics::Font> m_font;
		};
	}
};