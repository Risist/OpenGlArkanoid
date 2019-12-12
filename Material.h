#pragma once
#include "CoreInclude.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Rendering
{

	class Shader
	{
	public:
		~Shader()
		{
			if (shaderId != -1)
				glDeleteShader(shaderId);
		}
		bool loadCode(string_t code, GLenum shaderType)
		{
			shaderId = glCreateShader(shaderType);

			glShaderSource(shaderId, 1, &code, NULL);
			glCompileShader(shaderId);

			GLint status;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				char buffer[512];
				glGetShaderInfoLog(shaderId, 512, NULL, buffer);
				std::cout << buffer << "\n";
				return false;
			}

			return true;
		}
		bool loadCodeFromFile(const string& path, GLenum shaderType)
		{
			ifstream file;

			file.open(path);
			if (!file)
			{
				cerr << "can't open file: \"" << path << "\"\n";
				return false;
			}

			stringstream strStream;
			strStream << file.rdbuf();
			loadCode(strStream.str().c_str(), shaderType);
			return true;
		}

	private:
		GLuint shaderId = -1;
		friend class Material;
	};

	class Material
	{
	public:
		~Material()
		{
			if (programId != -1)
				glDeleteProgram(programId);
		}
		void InitProgram(string_t vertexShaderCode, string_t fragmentShaderCode)
		{
			programId = glCreateProgram();
			AttachFragmentShader(fragmentShaderCode);
			AttachVertexShader(vertexShaderCode);
			glLinkProgram(programId);
		}
		void InitProgramFromFile(string_t vertexShaderCode, string_t fragmentShaderCode)
		{
			programId = glCreateProgram();
			AttachFragmentShaderFromFile(fragmentShaderCode);
			AttachVertexShaderFromFile(vertexShaderCode);
			glLinkProgram(programId);
		}

	public: // usage
		void Bind() const
		{
			glUseProgram(programId);
		}
		inline GLuint GetAtribId(string_t name) const
		{
			return glGetAttribLocation(programId, name);
		}

	public: // uniform
		void SetUniform1f(const char* name, float value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform1f(attribId, value);
		}
		void SetUniform2f(string_t name, float value, float value2)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform2f(attribId, value, value2);
		}
		void SetUniform3f(string_t name, float value, float value2, float value3)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform3f(attribId, value, value2, value3);
		}
		void SetUniform4f(string_t name, float value, float value2, float value3, float value4)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform4f(attribId, value, value2, value3, value4);
		}

		void SetUniform1d(string_t name, double value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform1d(attribId, value);
		}
		void SetUniform2d(string_t name, double value, double value2)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform2d(attribId, value, value2);
		}
		void SetUniform3d(string_t name, double value, double value2, double value3)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform3d(attribId, value, value2, value3);
		}
		void SetUniform4d(string_t name, double value, double value2, double value3, double value4)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform4d(attribId, value, value2, value3, value4);
		}


		void SetUniform1fv(string_t name, GLsizei count, float* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform1fv(attribId, count, value);
		}
		void SetUniform2fv(string_t name, GLsizei count, glm::vec2* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform2fv(attribId, count, (const GLfloat*)value);
		}
		void SetUniform3fv(string_t name, GLsizei count, glm::vec3* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform3fv(attribId, count, (const GLfloat*)value);
		}
		void SetUniform4fv(string_t name, GLsizei count, glm::vec4* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform4fv(attribId, count, (const GLfloat*)value);
		}

		void SetUniform1dv(string_t name, GLsizei count, double* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform1dv(attribId, count, (const GLdouble*)value);

		}
		void SetUniform2dv(string_t name, GLsizei count, glm::dvec2* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform2dv(attribId, count, (const GLdouble*)value);
		}
		void SetUniform3dv(string_t name, GLsizei count, glm::dvec3* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform3dv(attribId, count, (const GLdouble*)value);
		}
		void SetUniform4dv(string_t name, GLsizei count, glm::dvec4* value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniform4dv(attribId, count, (const GLdouble*)value);
		}

		void SetUniformMat2fv(string_t name, const glm::mat2& value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniformMatrix2fv(attribId, 1, GL_FALSE, &value[0][0]);
		}
		void SetUniformMat3fv(string_t name, const glm::mat3& value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniformMatrix3fv(attribId, 1, GL_FALSE, &value[0][0]);
		}
		void SetUniformMat4fv(string_t name, const glm::mat4& value)
		{
			glUseProgram(programId);
			GLint attribId = glGetUniformLocation(programId, name);
			glUniformMatrix4fv(attribId, 1, GL_FALSE, &value[0][0]);
		}

		//... TODO : other types ...

	private:
		GLuint programId = -1;
		Shader vertexShader;
		Shader fragmentShader;

		void AttachVertexShader(string_t code)
		{
			vertexShader.loadCode(code, GL_VERTEX_SHADER);
			glAttachShader(programId, vertexShader.shaderId);
		}
		void AttachVertexShaderFromFile(string_t path)
		{
			vertexShader.loadCodeFromFile(path, GL_VERTEX_SHADER);
			glAttachShader(programId, vertexShader.shaderId);
		}

		void AttachFragmentShader(string_t code)
		{
			vertexShader.loadCode(code, GL_FRAGMENT_SHADER);
			glAttachShader(programId, vertexShader.shaderId);
		}
		void AttachFragmentShaderFromFile(string_t path)
		{
			vertexShader.loadCodeFromFile(path, GL_FRAGMENT_SHADER);
			glAttachShader(programId, vertexShader.shaderId);
		}
	};


	

}
