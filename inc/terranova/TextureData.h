#ifndef TerraNova_TextureData_h
#define TerraNova_TextureData_h

#include <string>

#include <yanecos/Data.h>

namespace terranova {

struct TextureData
: public Yanecos::Data<TextureData> {

	unsigned int width;
	unsigned int height;

	std::string key;

};

}

#endif
