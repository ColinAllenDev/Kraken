#include "kepch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Kraken {
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
		// Create empty vertex shader handle
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		const char *src = (const char*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &src, 0);

		// Compile vertex shader
		glCompileShader(vertexShader);

		// Error handling
		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == 0) {
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			KE_CORE_ASSERT(false, "ERROR::SHADER - Vertex shader compilation failure!");
			KE_CORE_ERROR("{0}", infoLog.data());

			return;
		}

		// Create empty fragment shader
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		src = (const char*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &src, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == 0) {
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			KE_CORE_ASSERT(false, "ERROR::SHADER - Fragment shader compilation failure!");
			KE_CORE_ERROR("{0}", infoLog.data());

			return;
		}

		// After succesfully compiling vertex and fragment shaders, we must link them.
		// Store program as RenderID member variable
		m_RendererID = glCreateProgram();

		// Attach shaders to program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		int isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == 0) {
			int maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			KE_CORE_ASSERT(false, "ERROR::SHADER - Shader linking failed!");
			KE_CORE_ERROR("{0}", infoLog.data());

			return;
		}

		// Always detach shaders after a successful link
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

}
