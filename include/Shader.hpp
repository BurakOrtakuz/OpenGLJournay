#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h> 
  
#include <string>

class Shader
{
private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    unsigned int getID() const;
};
  
#endif