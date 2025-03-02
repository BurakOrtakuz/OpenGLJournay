#include <Window.hpp>
#include <Utils.hpp>
#include <iostream>

Window::Window(const int size_x, const int size_y, const std::string title)
	: size_x(size_x), size_y(size_y), title(title)
{
	try
	{
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		this->window = Utils::errCheck<GLFWwindow*>(NULL, 
			glfwCreateWindow(this->size_x, this->size_y, this->title.c_str(), nullptr, nullptr), 
			"Failed to create GLFW this->window");
		glfwMakeContextCurrent(this->window);
		Utils::errCheck<int>(0, 
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), 
			"Failed to initialize GLAD");
		glViewport(0, 0, this->size_x, this->size_y);
	}catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
	}
}

Window::~Window()
{
	glfwTerminate();
}

Window::Window(const Window& other)
	: size_x(other.size_x), size_y(other.size_y), title(other.title)
{
	if(this == &other)
		return;
	this->window = other.getWindow();
	glfwMakeContextCurrent(this->window);
	glViewport(0, 0, size_x, size_y);
}

void Window::makeContextCurrent() const
{
	glfwMakeContextCurrent(this->window);
}

void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback) const
{
	glfwSetFramebufferSizeCallback(this->window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) const
{
	glfwSetCursorPosCallback(this->window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback) const
{
	glfwSetScrollCallback(this->window, callback);
}

void Window::setInputMode(int mode, int value) const
{
	glfwSetInputMode(this->window, mode, value);
}

void Window::setCameraForCallback(Camera &camera)
{
	glfwSetWindowUserPointer(this->window, &camera);
}

void Window::refreshWindow() const
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(this->window);
}

void Window::setShouldClose(bool value)
{
	glfwSetWindowShouldClose(this->window, value);
}

bool Window::getKeyPressed(int key) const
{
	return (glfwGetKey(this->window, key) == GLFW_PRESS);
}
GLFWwindow* Window::getWindow() const{return this->window;}

