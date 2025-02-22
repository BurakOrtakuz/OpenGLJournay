#ifndef UTILS_HPP
#define UTILS_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class Utils
{
private:
	Utils() = delete;
	~Utils() = delete;
	Utils(const Utils&) = delete;
	Utils& operator=(const Utils&) = delete;
public:
	template <typename T>
	static T errCheck(T errcnd, T res, std::string message)
	{
		if (res == errcnd)
			throw std::runtime_error(message);
		return res;
	}
};

#endif // UTILS_HPP