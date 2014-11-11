#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include <iostream>

class Camera
{
public:
	Camera();
	Camera(std::string cameraName);
	~Camera();

	/// The method stores the view matrix in a local matrix.
	void getView(glm::mat4 *view);

	/// The method stores the perspective matrix in a local matrix.
	void getPerspective(glm::mat4 *perspective);

	/// The method stores the orthographic matrix in a local matrix.
	void getOrtho(glm::mat4 *ortho);


	/// The projection is set to orthographic using parameters to describe the quader. The variable m_useOrtho ist set true.
	void setOrtho(float left, float right, float bottom, float top, float near, float far);
	
	/// the method returns the kind of projection using the value of the m_useOrtho variable.
	void getProjection(glm::mat4 *projection);
	
	/// near and far are setted and the projection matrix gets recomputed. m_useOrtho is set false.
	void setNearFar(float near, float far);
	
	/// The method stores the value of the member variables m_znear and m_zfar in local float variables.
	void getNearFar(float *near, float *far);

	/// The method sets width and height to assign a certain section that will be shown.
	void setWidthHeight(int width, int height);

	// the position is added because the player will be attached to the camera later
	///The method sets the position of the camera
	void setPosition(glm::vec4 position);

	///Returns the position of the camera
	glm::vec4 getPosition();

	void moveForward();
	void moveBackward();

	std::string getCameraName();

protected:
	std::string m_cameraName;
	float m_fov, m_znear, m_zfar;
	int m_width, m_height;
	bool m_useOrtho;

	glm::mat4 m_viewmatrix;
	glm::mat4 m_perspective;
	glm::mat4 m_ortho;

	glm::vec4 m_cameraPosition;
};

