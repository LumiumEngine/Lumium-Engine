#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

lumi::system::Camera::Camera()
{
	m_view = glm::mat4(1);
	m_projection = glm::mat4(1);
	m_cameraCenter = glm::vec3(1);
	m_cameraPos = glm::vec3(1);
	m_cameraUp = glm::vec3(0, 1, 0);
}

lumi::system::Camera::~Camera()
{
}

void lumi::system::Camera::setCameraPosition(glm::vec3 cameraPosition)
{
	m_cameraPos = cameraPosition;
}

void lumi::system::Camera::setCameraCenter(glm::vec3 cameraCenter)
{
	m_cameraCenter = cameraCenter;
}

void lumi::system::Camera::setCameraUp(glm::vec3 cameraUp)
{
	m_cameraUp = cameraUp;
}

void lumi::system::Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void lumi::system::Camera::setOrtho(float left, float right, float bottom, float top, float near , float far)
{
	m_projection = glm::ortho(left, right, bottom, top, near, far);
}

glm::mat4 lumi::system::Camera::getViewProj()
{
	return m_projection * getView();
}

glm::mat4 lumi::system::Camera::getView()
{
	m_view = glm::lookAt(m_cameraPos, m_cameraCenter, m_cameraUp);
	return m_view;
}

glm::mat4 lumi::system::Camera::getProj()
{
	return m_projection;
}
