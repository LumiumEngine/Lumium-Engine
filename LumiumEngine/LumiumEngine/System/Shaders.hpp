#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace lumi
{
    namespace system
    {
        class Shaders
        {
        public:
            Shaders();
            ~Shaders();
            void addShader(std::string shaderFile, unsigned int shaderType);
            void compileProgram();
            void useProgram();
            void unuseProgram();
			GLint getUniformLocation(std::string uniformName);
			
			void glUniform(GLuint location, GLuint data);
			void glUniform(GLuint location, GLint data);
			void glUniform(GLuint location, GLboolean data);
			void glUniform(GLuint location, GLfloat data);
			void glUniform(GLuint location, GLdouble data);
			void glUniform(GLuint location, glm::vec2 data);
			void glUniform(GLuint location, glm::vec3 data);
			void glUniform(GLuint location, glm::vec4 data);
			void glUniformMatrix(GLuint location, GLboolean transpose, glm::mat3 data);
			void glUniformMatrix(GLuint location, GLboolean transpose, glm::mat4 data);
        private:
			GLuint m_iProgramID;
			std::vector<GLuint> m_shaderIDs;
			bool m_isBound;
        };
	}
}