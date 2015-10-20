#ifndef TerraNova_VertexShader_h
#define TerraNova_VertexShader_h

#include <string>

#include <GL/glew.h>

#include <terranova/Shader.h>

namespace terranova {

class VertexShader
: public Shader {

public:
	VertexShader (std::string souce_code)
	: Shader (souce_code, GL_VERTEX_SHADER) {
	}

};

}

#endif
