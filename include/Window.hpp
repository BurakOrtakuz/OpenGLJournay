#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

#include <Window.hpp>
#include <Camera.hpp>

class Window
{
private:
    GLFWwindow* window;
    const int size_x;
    const int size_y;
    const std::string title;
    Window() = delete;
    Window& operator=(const Window&) = delete;
public:
    Window(const int size_x, const int size_y, const std::string title);
    ~Window();
    Window(const Window&);
    void makeContextCurrent() const;
    void setFramebufferSizeCallback(GLFWframebuffersizefun callback) const;
    void setCursorPosCallback(GLFWcursorposfun callback) const;
    void setScrollCallback(GLFWscrollfun callback) const;
    void setInputMode(int mode, int value) const;
    void setCameraForCallback(Camera &camera);
    void refreshWindow() const;
    GLFWwindow* getWindow() const;
    bool getKeyPressed(int key) const;
    bool shouldClose() const;
    void setShouldClose(bool value);
};

#endif // WINDOW_HPP