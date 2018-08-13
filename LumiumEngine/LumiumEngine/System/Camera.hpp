#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace lumi
{
	namespace system
	{
		enum class CameraType {Ortho, Perspective};

		class Camera
		{
		public:
			Camera();
			~Camera();

			void setCameraPosition(glm::vec3 cameraPosition);
			void setCameraCenter(glm::vec3 cameraDirection);
			void setCameraUp(glm::vec3 cameraUp);

			void setPerspective(float fov, float aspectRatio, float near, float far);
			void setOrtho(float left, float right, float bottom, float top, float near, float far);

			glm::mat4 getViewProj();
			glm::mat4 getView();
			glm::mat4 getProj();
		private:
			glm::vec3 m_cameraPos, m_cameraCenter, m_cameraUp;
			glm::mat4 m_view, m_projection;
		};
	}
}