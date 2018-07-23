#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace lumi
{
	namespace graphics
	{
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Color;
			glm::vec3 Normal;
			glm::vec2 TexCoord;
		};
	};
}