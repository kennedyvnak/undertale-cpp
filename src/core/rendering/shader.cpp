#include <GL/glew.h>

#include <iostream> 
#include <fstream>
#include <sstream>

#include "shader.h"
#include "utility/open_gl_handler.h"

Shader::Shader(const String& filename)
    : _filepath(filename), _id(0) {
    ShaderProgramSource source = parse_shader(filename);
    _id = create_shader(source.vertex_source, source.fragment_source);
}

Shader::~Shader() {
    GL_CALL(glDeleteProgram(_id));
}


void Shader::bind() const {
    GL_CALL(glUseProgram(_id));
}

void Shader::unbind() const {
    GL_CALL(glUseProgram(0));
}

int Shader::get_uniform_location(const String& name) const {
    auto location_search = _uniform_location_cache.find(name);
    if (location_search != _uniform_location_cache.end()) {
        return location_search->second;
    }

    GL_CALL(int location = glGetUniformLocation(_id, name.c_str()));
    ASSERT(location != -1);
    _uniform_location_cache[name] = location;
    return location;
}

void Shader::set_uniform_int(const String& name, int value) {
    GL_CALL(glUniform1i(get_uniform_location(name), value));
}

void Shader::set_uniform_float(const String& name, float value) {
    GL_CALL(glUniform1f(get_uniform_location(name), value));
}

void Shader::set_uniform_vector2(const String& name, const Vector2& value) {
    GL_CALL(glUniform2f(get_uniform_location(name), value.x, value.y));
}

void Shader::set_uniform_vector3(const String& name, const Vector3& value) {
    GL_CALL(glUniform3f(get_uniform_location(name), value.x, value.y, value.z));
}

void Shader::set_uniform_vector4(const String& name, const Vector4& value) {
    GL_CALL(glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w));
}

void Shader::set_uniform_matrix(const String& name, const Matrix& value) {
    GL_CALL(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value)));
}

ShaderProgramSource Shader::parse_shader(const String& filename) {
    std::ifstream stream(_filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    String line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != String::npos) {
            if (line.find("vertex") != String::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != String::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile_shader(unsigned int type, const String& source) {
    GL_CALL(unsigned int id = glCreateShader(type));

    const char* src = source.c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr));
    GL_CALL(glCompileShader(id));

    int result;
    GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader! " << std::endl;
        std::cout << message << std::endl;
        GL_CALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const String& vert_shader_source, const String& frag_shader_source) {
    GL_CALL(unsigned int program = glCreateProgram());
    unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vert_shader_source);
    unsigned int fragment_shader = compile_shader(GL_FRAGMENT_SHADER, frag_shader_source);

    GL_CALL(glAttachShader(program, vertex_shader));
    GL_CALL(glAttachShader(program, fragment_shader));
    GL_CALL(glLinkProgram(program));
    GL_CALL(glValidateProgram(program));

    GL_CALL(glDeleteShader(vertex_shader));
    GL_CALL(glDeleteShader(fragment_shader));

    return program;
}