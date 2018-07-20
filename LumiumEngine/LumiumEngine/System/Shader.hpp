#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace lumi
{
    namespace system
    {
        class Shader
        {
        public:
            Shader();
            ~Shader();
            void addShader(std::string shaderFile, unsigned int shaderType);
            void compileProgram();
            void useProgram();
            void unuseProgram();
			GLint getUniformLocation(std::string uniformName);

			// glUniform specialization
			template<class T>
			void glUniform(GLuint location, T data);
			template<>
			void glUniform(GLuint location, GLuint data);
			template<>
			void glUniform(GLuint location, GLint data);
			template<>
			void glUniform(GLuint location, GLboolean data);
			template<>
			void glUniform(GLuint location, GLfloat data);
			template<>
			void glUniform(GLuint location, GLdouble data);
			template<>
			void glUniform(GLuint location, glm::vec2 data);
			template<>
			void glUniform(GLuint location, glm::vec3 data);
			template<>
			void glUniform(GLuint location, glm::vec4 data);
			template<class T>
			void glUniformMatrix(GLuint location, GLboolean transpose, T data);
			template<>
			void glUniformMatrix(GLuint location, GLboolean transpose, glm::mat3 data);
			template<>
			void glUniformMatrix(GLuint location, GLboolean transpose, glm::mat4 data);
        private:
			GLuint m_iProgramID;
			std::vector<GLuint> m_shaderIDs;
        };
	}
}