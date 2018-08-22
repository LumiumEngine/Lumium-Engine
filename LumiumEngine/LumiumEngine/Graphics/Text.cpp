#include "Text.hpp"

lumi::graphics::Text::Text()
{
}

lumi::graphics::Text::~Text()
{
}

/*
const std::string text = "Rotating in world space";

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<uint16_t> indexes;

		uint16_t lastIndex = 0;
		float offsetX = 0, offsetY = 0;
		for (auto c : text)
		{
			const auto glyphInfo = getGlyphInfo(c, offsetX, offsetY);
			offsetX = glyphInfo.offsetX;
			offsetY = glyphInfo.offsetY;

			vertices.emplace_back(glyphInfo.positions[0]);
			vertices.emplace_back(glyphInfo.positions[1]);
			vertices.emplace_back(glyphInfo.positions[2]);
			vertices.emplace_back(glyphInfo.positions[3]);
			uvs.emplace_back(glyphInfo.uvs[0]);
			uvs.emplace_back(glyphInfo.uvs[1]);
			uvs.emplace_back(glyphInfo.uvs[2]);
			uvs.emplace_back(glyphInfo.uvs[3]);
			indexes.push_back(lastIndex);
			indexes.push_back(lastIndex + 1);
			indexes.push_back(lastIndex + 2);
			indexes.push_back(lastIndex);
			indexes.push_back(lastIndex + 2);
			indexes.push_back(lastIndex + 3);

			lastIndex += 4;
		}

		glGenVertexArrays(1, &rotatingLabel.vao);
		glBindVertexArray(rotatingLabel.vao);

		glGenBuffers(1, &rotatingLabel.vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, rotatingLabel.vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &rotatingLabel.uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, rotatingLabel.uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);

		rotatingLabel.indexElementCount = indexes.size();
		glGenBuffers(1, &rotatingLabel.indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rotatingLabel.indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * rotatingLabel.indexElementCount, indexes.data(), GL_STATIC_DRAW);

		
	void renderRotatingLabel(float dt)
	{
		rotatingLabel.angle += dt;

		const auto worldMatrix = glm::scale(
			glm::rotate(
				glm::translate(glm::mat4{}, {0, 5, -30}),
				rotatingLabel.angle,
				{0, 1, 0}),
			{0.05f, 0.05f, 1});
		glUniformMatrix4fv(program.uniforms.worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));

		glBindVertexArray(rotatingLabel.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rotatingLabel.indexBuffer);
		glDrawElements(GL_TRIANGLES, rotatingLabel.indexElementCount, GL_UNSIGNED_SHORT, nullptr);
	}

		*/