#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_images/stb_image.h>

#include <Shader.hpp>
#include <Utils.hpp>
#include <Window.hpp>
#include <Camera.hpp>
#include <Model.hpp>

#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(Window &window, Shader &ourShader);
// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
int main()
{
	Window window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	window.makeContextCurrent();
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	window.setCameraForCallback(camera);
	window.setFramebufferSizeCallback(framebuffer_size_callback);
	window.setCursorPosCallback(mouse_callback);
	window.setScrollCallback(scroll_callback);
	window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
    stbi_set_flip_vertically_on_load(true);
	Shader ourShader("./lib/Shaders/shader.vs", "./lib/Shaders/shader.fs");
    Model ourModel("./assets/backpack/backpack.obj");

	float time = 0.0f;
	while (!window.shouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window,ourShader);

		// render
		// ------

		float r = (sin(time) + 1.0f) / 2.0f;
        float g = (sin(time + 2.0f) + 1.0f) / 2.0f;
        float b = (sin(time + 4.0f) + 1.0f) / 2.0f;
		time+=0.0f;
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, static_cast<float>(glfwGetTime()*1), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);

		ourShader.setFloat("angle", glfwGetTime()*100);
		ourModel.Draw(ourShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		window.refreshWindow();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(Window &window,Shader &ourShader)
{
	Camera *camera = static_cast<Camera*>(glfwGetWindowUserPointer(window.getWindow()));
	if (window.getKeyPressed(GLFW_KEY_ESCAPE))
		window.setShouldClose(true);
	if (window.getKeyPressed(GLFW_KEY_W) || window.getKeyPressed(GLFW_KEY_UP))
		camera->processKeyboard(Camera::Camera_Movement::FORWARD, deltaTime);
	if (window.getKeyPressed(GLFW_KEY_S) || window.getKeyPressed(GLFW_KEY_DOWN))
		camera->processKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime);
	if (window.getKeyPressed(GLFW_KEY_A) || window.getKeyPressed(GLFW_KEY_LEFT))
		camera->processKeyboard(Camera::Camera_Movement::LEFT, deltaTime);	
	if (window.getKeyPressed(GLFW_KEY_D) || window.getKeyPressed(GLFW_KEY_RIGHT))
		camera->processKeyboard(Camera::Camera_Movement::RIGHT, deltaTime);
	if(window.getKeyPressed(GLFW_KEY_SPACE))
		camera->processKeyboard(Camera::Camera_Movement::UP,deltaTime);
	if(window.getKeyPressed(GLFW_KEY_LEFT_SHIFT))
		camera->processKeyboard(Camera::Camera_Movement::DOWN,deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
	static float lastX = SCR_WIDTH / 2;
	static float lastY = SCR_HEIGHT / 2;
	static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
	Camera *camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	camera->processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera *camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	camera->processMouseScroll(yoffset);
}