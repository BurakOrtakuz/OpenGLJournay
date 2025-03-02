#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	constexpr static float defaultYaw = -90.0f;
	constexpr static float defaultPitch = 0.0f;
	constexpr static float defaultSpeed = 2.5f;
	constexpr static float defaultSensitivity = 0.1f;
	constexpr static float defaultZoom = 45.0f;
	// Camera Attributes
	glm::vec3   cameraPosition;
	glm::vec3   cameraFront;
	glm::vec3  	cameraUp;
	glm::vec3   cameraRight;
	glm::vec3   worldUp;

	// Euler Angles
	float yaw;
	float pitch;

	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	// Camera Functions
	void updateCameraVectors();
public:
	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = defaultYaw, float pitch = defaultPitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();
	Camera(const Camera &camera);
	Camera &operator=(const Camera &camera);
	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void processMouseScroll(float yoffset);
	glm::mat4 getViewMatrix() const;
	float getZoom() const;
	glm::vec3 getPosition() const;

};

#endif // CAMERA_HPP