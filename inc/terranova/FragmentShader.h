#ifndef TerraNova_FragmentShader_h
#define TerraNova_FragmentShader_h

#include <string>

#include <GL/glew.h>

#include <terranova/Shader.h>

namespace terranova {

class FragmentShader
: public Shader {

public:
	FragmentShader (std::string souce_code)
	: Shader (souce_code, GL_FRAGMENT_SHADER) {
	}

};

}

#endif
