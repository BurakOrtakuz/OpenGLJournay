#include <Camera.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : cameraPosition(position),
      cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      worldUp(up),
      yaw(yaw),
      pitch(pitch),
      movementSpeed(defaultSpeed),
      mouseSensitivity(defaultSensitivity),
      zoom(defaultZoom)
{
    updateCameraVectors();
}

Camera::Camera( float posX, float posY, float posZ,
                float upX, float upY, float upZ, 
                float yaw, float pitch)
    : cameraPosition(glm::vec3(posX, posY, posZ)),
      cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      worldUp(glm::vec3(upX, upY, upZ)),
      yaw(yaw),
      pitch(pitch),
      movementSpeed(defaultSpeed),
      mouseSensitivity(defaultSensitivity),
      zoom(defaultZoom)
{
    updateCameraVectors();
}

Camera::~Camera()
{
}

Camera::Camera(const Camera &camera)
{
    if (this == &camera)
        return;
    cameraPosition = camera.cameraPosition;
    cameraFront = camera.cameraFront;
    cameraUp = camera.cameraUp;
    cameraRight = camera.cameraRight;
    worldUp = camera.worldUp;
    yaw = camera.yaw;
    pitch = camera.pitch;
    movementSpeed = camera.movementSpeed;
    mouseSensitivity = camera.mouseSensitivity;
    zoom = camera.zoom;
    updateCameraVectors();
}

Camera &Camera::operator=(const Camera &camera)
{
    if (this == &camera)
        return *this;
    cameraPosition = camera.cameraPosition;
    cameraFront = camera.cameraFront;
    cameraUp = camera.cameraUp;
    cameraRight = camera.cameraRight;
    worldUp = camera.worldUp;
    yaw = camera.yaw;
    pitch = camera.pitch;
    movementSpeed = camera.movementSpeed;
    mouseSensitivity = camera.mouseSensitivity;
    zoom = camera.zoom;
    updateCameraVectors();
    return *this;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        cameraPosition += cameraFront * velocity;
    if (direction == Camera_Movement::BACKWARD)
        cameraPosition -= cameraFront * velocity;
    if (direction == Camera_Movement::LEFT)
        cameraPosition -= cameraRight * velocity;
    if (direction == Camera_Movement::RIGHT)
        cameraPosition += cameraRight * velocity;
    if (direction == Camera_Movement::UP)
        cameraPosition += cameraUp * velocity;
    if (direction == Camera_Movement::DOWN)
        cameraPosition -= cameraUp * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

float Camera::getZoom() const
{
    return zoom;
}

glm::vec3 Camera::getPosition() const
{
    return cameraPosition;
}