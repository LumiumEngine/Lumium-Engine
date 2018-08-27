#pragma once
#include <LumiumEngine/Graphics/Drawable.hpp>

namespace lumi
{
	namespace graphics
	{
		class Square : public lumi::graphics::Drawable
		{
		public:
			Square();
			~Square();
		private:
			void createSquare();
		};
	}
}