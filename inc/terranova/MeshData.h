#ifndef TerraNova_MeshData_h
#define TerraNova_MeshData_h

#include <string>

#include <yanecos/Data.h>

namespace terranova {

struct MeshData
: public Yanecos::Data<MeshData> {

	MeshData (const std::string &key)
	: key (key) {
		//
	}

	virtual
	~MeshData (void) {
		//
	}

	std::string key;

};

}

#endif
