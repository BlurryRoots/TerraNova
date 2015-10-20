#ifndef TerraNova_Shader_h
#define TerraNova_Shader_h

// std shit
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <map>

#include <GL/glew.h>

#include <blurryroots/throwif.h>

#include <terranova/FileReader.h>

namespace terranova {

class Shader {

public:
	bool
	is_valid (void) const {
		return glIsShader (this->handle);
	}

	void
	dispose (void) {
		if (this->is_valid ()) {
			glDeleteShader (this->handle);
		}
	}

	GLuint
	get_handle (void) const {
		return this->handle;
	}

protected:
	Shader (std::string source_code, GLenum type)
	: handle (0)
	, type (type) {
		this->handle = glCreateShader (this->type);

		const char *src_lines[] = {
			(const char *)source_code.c_str ()
		};
		glShaderSource (
			this->handle,
			sizeof (src_lines) / sizeof (src_lines[0]),
			src_lines,
			NULL
		);

		glCompileShader (this->handle);

		std::string msg;
		THROW_IF (this->has_errors (msg),
			"Error in shader:\n", msg
		);
	}

private:
	GLuint handle;
	GLenum type;

	bool
	has_errors (std::string &error_message) {
		GLint compiled = 0;
		glGetShaderiv (this->handle, GL_COMPILE_STATUS, &compiled);

		bool status = false;
		if (GL_FALSE == compiled) {
			GLint logSize;
			glGetShaderiv (this->handle, GL_INFO_LOG_LENGTH, &logSize);

			/*block for log message retrieval*/ {
				char logMessage[logSize];
				glGetShaderInfoLog (this->handle, logSize, NULL, logMessage);
				error_message = (logMessage);
			}

			status = true;
		}

		return status;
	}

};

}

#endif
