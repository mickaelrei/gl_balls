#ifndef SHADER_H
#define SHADER_H

#include <include/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // the program id
    unsigned int id;

    // Constructor
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    // Use/activate shader
    void Use() const;

    // Destroy shader
    void Destroy() const;

    // Set uniform bool in shader
    void SetBool(const std::string &name, bool value) const;

    // Set uniform int in shader
    void SetInt(const std::string &name, int value) const;

    // Set uniform float in shader
    void SetFloat(const std::string &name, float value) const;

    // Set uniform vec2 in shader
    void SetVec2(const std::string &name, glm::vec2 &v) const;

    // Set uniform vec3 in shader
    void SetVec3(const std::string &name, glm::vec3 &v) const;

    // Set uniform vec4 in shader
    void SetVec4(const std::string &name, glm::vec4 &v) const;

    // Set uniform mat4 in shader
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif // SHADER_H