#pragma once
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
		// glUniform specialization
		template<class T>
		inline void Shaders::glUniform(GLuint location, T data)
		{
			std::cout << "Invalid glUniform function paramaters called\n";
		}
		template<>
		inline void Shaders::glUniform(GLuint location, GLuint data)
		{
			glUniform1ui(location, data);
		}
		template<>
		inline void Shaders::glUniform(GLuint location, GLint data)
		{
			glUniform1i(location, data);
		}
		template<>
		inline void Shaders::glUniform(GLuint location, GLboolean data)
		{
			glUniform1i(location, data);
		}
		template<>
		inline void Shaders::glUniform(GLuint location, GLfloat data)
		{
			glUniform1f(location, data);
		}
		template<>
		inline void Shaders::glUniform(GLuint location, GLdouble data)
		{
			glUniform1d(location, data);
		}
		template<>
		inline void Shaders::glUniform(GLuint location, glm::vec2 data)
		{
			glUniform2fv(location, 1, glm::value_ptr(data));
		}
		template<>
		inline void Shaders::glUniform(GLuint location, glm::vec3 data)
		{
			glUniform3fv(location, 1, glm::value_ptr(data));
		}
		template<>
		inline void Shaders::glUniform(GLuint location, glm::vec4 data)
		{
			glUniform4fv(location, 1, glm::value_ptr(data));
		}
		template<class T>
		inline void Shaders::glUniformMatrix(GLuint location, GLboolean transpose, T data)
		{
			std::cout << "Invalid glUniformMatrix function paramaters called\n";
		}
		template<>
		inline void Shaders::glUniformMatrix(GLuint location, GLboolean transpose, glm::mat3 data)
		{
			glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(data));
		}
		template<>
		inline void Shaders::glUniformMatrix(GLuint location, GLboolean transpose, glm::mat4 data)
		{
			glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(data));
		}

	}
}