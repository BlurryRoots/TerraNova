#ifndef TerraNova_IResource_h
#define TerraNova_IResource_h

// TODO: think about a resouce baseclass used to track
// allocated resouces and their disposal (and any lack thereof)

namespace terranova {

class IResource {

public:
	virtual
	~IResource (void) {
		//
	}

};

}

#endif
