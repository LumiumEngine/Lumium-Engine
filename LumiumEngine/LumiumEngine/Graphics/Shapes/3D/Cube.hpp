#pragma once
#include <LumiumEngine/Graphics/Drawable.hpp>
#include <LumiumEngine/Graphics/Vertex.hpp>
#include <glad/glad.h>

namespace lumi
{
	namespace graphics
	{
		class Cube : public Drawable
		{
		public:
			Cube();
			~Cube();
		private:
			void createCube();
		};
	}
}