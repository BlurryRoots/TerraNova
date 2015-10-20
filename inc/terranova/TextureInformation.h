#ifndef TerraNova_TextureInformation_h
#define TerraNova_TextureInformation_h

#include <GL/glew.h>

#include <ostream>

namespace terranova {

struct TextureInformation {

	TextureInformation ()
	: texels (nullptr)
	, handle (0) {
		//
	}

	friend std::ostream&
	operator << (std::ostream &s, const TextureInformation &info) {
		s 	<< "handle: " << info.handle
			<< "\nw/h: " << info.width << "/" << info.height
			<< "\ncomponents: " << info.components
			<< "\nformat: " << info.format
			<< "\ninternal format: " << info.internalFormat
			<< "\ntexture_unit: " << info.texture_unit
			<< std::endl;

		return s;
	}

	GLubyte *texels;

	GLuint handle;

	GLint width;
	GLint height;

	GLint components;

	GLenum format;
	GLint internalFormat;

	std::string path;
	std::string key;

	GLuint texture_unit;

};

}

#endif
