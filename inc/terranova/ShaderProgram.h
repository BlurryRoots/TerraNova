#ifndef TerraNova_ShaderProgram_h
#define TerraNova_ShaderProgram_h

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <terranova/VertexShader.h>
#include <terranova/FragmentShader.h>

#include <blurryroots/throwif.h>

#define DEBUG_MESSAGE

namespace terranova {

class ShaderProgram {
friend class ShaderProgramBuilder;

public:
	ShaderProgram (void) {
	}

	virtual
	~ShaderProgram (void) {
	}

	void
	use (void) {
		in_use = true;
		glUseProgram (this->handle);
	}

	void
	deactivate (void) {
		in_use = false;
		glUseProgram (0);
	}

	void
	dispose (void) {
		glDeleteProgram (this->handle);
	}

	GLuint
	get_handle (void) const {
		return this->handle;
	}

	GLint
	get_attribute_location (const std::string name) {
		if (0 == this->attributes.count (name)) {
			GLint location = glGetAttribLocation (this->handle,
				name.c_str ()
			);

			THROW_IF (0 > location,
				"Could not find attribute ", name
			);

			const auto &r = this->attributes.emplace (name, location);
			THROW_IF (! r.second, "Trying to override ", name);
		}

		return this->attributes.at (name);
	}

	void
	set_uniform_mat4 (const std::string &name, const glm::mat4 &matrix) {
		std::size_t c = this->uniforms.count (name);
		if (0 == c) {
			GLint loc = glGetUniformLocation (this->handle,
				name.c_str ()
			);
			THROW_IF (0 > loc,
				"Could not find ", name, " ", std::to_string (c)
			);

			this->uniforms.emplace (name, loc);
		}

		THROW_IF (! this->in_use,
			"Unable to set uniform without activating program!"
		);

		glUniformMatrix4fv (
			this->uniforms.at (name),
			1,
			GL_FALSE,
			//&matrix[0][0]
			glm::value_ptr (matrix)
		);
	}

	void
	set_uniform_vec3 (const std::string &name, const glm::vec3 &vec) {
		this->set_uniform_vec3_array (name, &vec, 1);
	}

	void
	set_uniform_vec3_array (const std::string &name, const glm::vec3 *vec_arr, std::size_t count) {
		THROW_IF (nullptr == vec_arr,
			"Array pointer null!"
		);
		THROW_IF (0 == count,
			"Count is zero!"
		);

		std::size_t c = this->uniforms.count (name);
		if (0 == c) {
			GLint loc = glGetUniformLocation (this->handle,
				name.c_str ()
			);
			THROW_IF (0 > loc,
				"Could not find ", name, " ", std::to_string (c)
			);

			this->uniforms.emplace (name, loc);
		}

		THROW_IF (! this->in_use,
			"Unable to set uniform without activating program!"
		);

		glUniform3fv (
			this->uniforms.at (name),
			count,
			glm::value_ptr (vec_arr[0])
		);
	}

	void
	set_uniform_vec4 (const std::string &name, const glm::vec4 &vec) {
		this->set_uniform_vec4_array (name, &vec, 1);
	}

	void
	set_uniform_vec4_array (const std::string &name, const glm::vec4 *vec_arr, std::size_t count) {
		THROW_IF (nullptr == vec_arr,
			"Array pointer null!"
		);
		THROW_IF (0 == count,
			"Count is zero!"
		);

		std::size_t c = this->uniforms.count (name);
		if (0 == c) {
			GLint loc = glGetUniformLocation (this->handle,
				name.c_str ()
			);
			THROW_IF (0 > loc,
				"Could not find ", name, " ", std::to_string (c)
			);

			this->uniforms.emplace (name, loc);
		}

		THROW_IF (! this->in_use,
			"Unable to set uniform without activating program!"
		);

		glUniform4fv (
			this->uniforms.at (name),
			count,
			glm::value_ptr (vec_arr[0])
		);
	}

	void
	set_uniform_f (const std::string &name, float value) {
		THROW_IF (0 == this->uniforms.count (name),
			"Could not find ", name
		);

		THROW_IF (! this->in_use,
			"Unable to set uniform without activating program!"
		);

		glUniform1f (
			this->uniforms.at (name),
			value
		);
	}

	GLfloat
	get_uniform_f (const std::string &name) const {
		int uid = glGetUniformLocation (this->handle, name.c_str ());

		GLfloat value;
		glGetUniformfv (
			this->handle,
			uid,
			&value
		);

		return value;
	}

	void
	set_uniform_i (const std::string &name, int value) {
		THROW_IF (0 == this->uniforms.count (name),
			"Could not find ", name
		);

		THROW_IF (! this->in_use,
			"Unable to set uniform without activating program!"
		);

		glUniform1i (
			this->uniforms.at (name),
			value
		);
	}

	GLint
	get_uniform_i (const std::string &name) const {
		int uid = glGetUniformLocation (this->handle, name.c_str ());
		GLint value;
		glGetUniformiv (
			this->handle,
			uid,
			&value
		);

		return value;
	}

	GLuint
	get_uniform_ui (const std::string &name) const {
		int uid = glGetUniformLocation (this->handle, name.c_str ());
		GLuint value;
		glGetUniformuiv (
			this->handle,
			uid,
			&value
		);

		return value;
	}

	GLdouble
	get_uniform_d (const std::string &name) const {
		int uid = glGetUniformLocation (this->handle, name.c_str ());
		GLdouble value;
		glGetUniformdv (
			this->handle,
			uid,
			&value
		);

		return value;
	}

private:
	bool in_use;
	GLuint handle;

	std::unordered_map<std::string, GLuint> uniforms;
	std::unordered_map<std::string, GLint> attributes;

};

class ShaderProgramBuilder {

private:
	ShaderProgram program;

	bool has_vert;
	bool has_frag;

	std::string
	get_info_log (ShaderProgram program) {
		GLint log_length;
		glGetProgramiv (program.handle, GL_INFO_LOG_LENGTH, &log_length);

		char log_buffer[log_length];
		glGetProgramInfoLog (program.handle, log_length, NULL, log_buffer);

		return std::string (log_buffer);
	}

	bool
	is_deleted (ShaderProgram program) {
		GLint value;
		glGetProgramiv (program.handle, GL_DELETE_STATUS, &value);

		if (GL_TRUE == value) {
			return true;
		}

		if (GL_FALSE == value) {
			return false;
		}

		throw this->get_info_log (program);
	}

	bool
	is_linked (ShaderProgram program) {
		GLint value;
		glGetProgramiv (program.handle, GL_LINK_STATUS, &value);

		if (GL_TRUE == value) {
			return true;
		}

		if (GL_FALSE == value) {
			return false;
		}

		throw this->get_info_log (program);
	}

	bool
	is_validated (ShaderProgram program) {
		GLint value;
		glGetProgramiv (program.handle, GL_VALIDATE_STATUS, &value);

		if (GL_TRUE == value) {
			return true;
		}

		if (GL_FALSE == value) {
			return false;
		}

		throw this->get_info_log (program);
	}
//GL_INFO_LOG_LENGTH
//
//    params returns the number of characters in the information log for program including the null termination character (i.e., the size of the character buffer required to store the information log). If program has no information log, a value of 0 is returned.
//GL_ATTACHED_SHADERS
//
//    params returns the number of shader objects attached to program.
//GL_ACTIVE_ATOMIC_COUNTER_BUFFERS
//
//    params returns the number of active attribute atomic counter buffers used by program.
//GL_ACTIVE_ATTRIBUTES
//
//    params returns the number of active attribute variables for program.
//GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
//
//    params returns the length of the longest active attribute name for program, including the null termination character (i.e., the size of the character buffer required to store the longest attribute name). If no active attributes exist, 0 is returned.
//GL_ACTIVE_UNIFORMS
//
//    params returns the number of active uniform variables for program.
//GL_ACTIVE_UNIFORM_MAX_LENGTH
//
//    params returns the length of the longest active uniform variable name for program, including the null termination character (i.e., the size of the character buffer required to store the longest uniform variable name). If no active uniform variables exist, 0 is returned.
//GL_PROGRAM_BINARY_LENGTH
//
//    params returns the length of the program binary, in bytes that will be returned by a call to glGetProgramBinary. When a progam's GL_LINK_STATUS is GL_FALSE, its program binary length is zero.
//GL_COMPUTE_WORK_GROUP_SIZE
//
//    params returns an array of three integers containing the local work group size of the compute program as specified by its input layout qualifier(s). program must be the name of a program object that has been previously linked successfully and contains a binary for the compute shader stage.
//GL_TRANSFORM_FEEDBACK_BUFFER_MODE
//
//    params returns a symbolic constant indicating the buffer mode used when transform feedback is active. This may be GL_SEPARATE_ATTRIBS or GL_INTERLEAVED_ATTRIBS.
//GL_TRANSFORM_FEEDBACK_VARYINGS
//
//    params returns the number of varying variables to capture in transform feedback mode for the program.
//GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
//
//    params returns the length of the longest variable name to be used for transform feedback, including the null-terminator.
//GL_GEOMETRY_VERTICES_OUT
//
//    params returns the maximum number of vertices that the geometry shader in program will output.
//GL_GEOMETRY_INPUT_TYPE
//
//    params returns a symbolic constant indicating the primitive type accepted as input to the geometry shader contained in program.
//GL_GEOMETRY_OUTPUT_TYPE
//
//    params returns a symbolic constant indicating the primitive type that will be output by the geometry shader contained in program.

public:
	ShaderProgramBuilder (void) {
		this->program.handle = glCreateProgram ();
		bool invalid = GL_FALSE == glIsProgram (this->program.handle);
		THROW_IF (invalid,
			"Program handle creation failed!"
		);
	}

	virtual
	~ShaderProgramBuilder (void) {
	}

	ShaderProgramBuilder&
	add_shader (VertexShader vs) {
		this->has_vert = true;
		glAttachShader (this->program.handle, vs.get_handle ());

		return *this;
	}

	ShaderProgramBuilder &
	add_shader (FragmentShader fs) {
		this->has_frag = true;
		glAttachShader (this->program.handle, fs.get_handle ());

		return *this;
	}

	ShaderProgramBuilder &
	bind_attribute (const std::string &name, GLuint location) {
		glBindAttribLocation (this->program.handle, location, name.c_str ());

		return *this;
	}

	ShaderProgram
	link (void) {
		THROW_IF (! this->has_vert,
			"ShaderProgram has no vertex shader attached!"
		);

		THROW_IF (! this->has_frag,
			"ShaderProgram has no fragment shader attached!"
		);

		glLinkProgram (this->program.handle);
		THROW_IF (! this->is_linked (this->program),
			"Error linking program: ", this->get_info_log (this->program)
		);

		glValidateProgram (this->program.handle);
		THROW_IF (! this->is_validated (this->program),
			"Error validating program: ", this->get_info_log (this->program)
		);


		// search all active uniforms and cache their locations
		GLint number_uniforms;
		glGetProgramiv (this->program.handle,
			GL_ACTIVE_UNIFORMS,
			&number_uniforms
		);
		THROW_IF (0 == number_uniforms,
			SOURCE_LOCATION, "No uniforms found!"
		);

		#ifdef DEBUG_MESSAGE
		std::cout << "Found " << number_uniforms << " uniforms" << std::endl;
		#endif

		GLuint n = static_cast<GLuint> (number_uniforms);
		for (GLuint index = 0; index < n; ++index) {
			char name_buffer[100];
			GLsizei name_buffer_size = sizeof (name_buffer);
			GLint uniform_type_size;
			GLenum uniform_type;
			GLsizei actual_size;

			glGetActiveUniform (this->program.handle,
				index,
				name_buffer_size,
				&actual_size,
				&uniform_type_size,
				&uniform_type,
				name_buffer
			);

			THROW_IF (0 == name_buffer_size,
				"Uniform @", std::to_string (index), " has no name ?!"
			);

			const auto &report =
				this->program.uniforms.emplace (name_buffer, index);
			THROW_IF (! report.second,
				"There is already a uniform with the name ", name_buffer
			);

			#ifdef DEBUG_MESSAGE
			std::cout << "Found uniform "
				<< report.first->first << "/" << name_buffer
				<< "@" << report.first->second
				<< std::endl;
			#endif

		}

		// voi la
		return this->program;
	}

};

}

#endif
