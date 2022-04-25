#include "gfx.hpp"
#include "gl/gl_core_3_2.hpp"

namespace Gfx {

static std::string getShaderLog(GLuint shader) {
    if (gl::IsShader(shader)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        gl::GetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;

        return message;
    } else {
        return "Wrong shader handle";
    }
}

static std::string getProgramLog(GLuint shaderProgram) {
    if (gl::IsProgram(shaderProgram)) {
        std::string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        gl::GetProgramiv(shaderProgram, gl::INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        gl::GetProgramInfoLog(shaderProgram, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;
        return message;
    } else {
        return "Wrong shader program handle";
    }
}

static GLuint compileShader(std::string source, GLenum shaderType) {
    GLuint shader = gl::CreateShader(shaderType);
    const GLchar* lines[] = {
        source.c_str()};
    gl::ShaderSource(shader, 1, lines, NULL);
    gl::CompileShader(shader);
    GLint isCompiled = gl::FALSE_;
    gl::GetShaderiv(shader, gl::COMPILE_STATUS, &isCompiled);
    if (isCompiled != gl::TRUE_) {
        std::string msg;
        if (shaderType == gl::VERTEX_SHADER) {
            msg = "Vertex shader compile error: ";
        } else if (shaderType == gl::FRAGMENT_SHADER) {
            msg = "Fragment shader compile error: ";
        } else {
            msg = "Shader compile error: ";
        }
        error_message("Shader compile error", msg + getShaderLog(shader));
        return 0;
    }
    return shader;
}

GLuint compileShaderProgram(const std::string vertexShaderCode, const std::string fragmentShaderCode) {
    GLuint program = gl::CreateProgram();

    GLuint compiledVertexShader = compileShader(vertexShaderCode, gl::VERTEX_SHADER);
    GLuint compiledFragmentShader = compileShader(fragmentShaderCode, gl::FRAGMENT_SHADER);

    gl::AttachShader(program, compiledVertexShader);
    gl::AttachShader(program, compiledFragmentShader);
    gl::LinkProgram(program);
    GLint result = gl::FALSE_;
    gl::GetProgramiv(program, gl::LINK_STATUS, &result);
    if (result != gl::TRUE_) {
        error_message("Shader link error", getProgramLog(program));
        return 0;
    }
    gl::DeleteShader(compiledVertexShader);
    gl::DeleteShader(compiledFragmentShader);
    return program;
};

}  // namespace Gfx