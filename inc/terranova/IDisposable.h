#ifndef TerraNova_IDisposable_h
#define TerraNova_IDisposable_h

namespace terranova {

struct IDisposable {
	virtual
	~IDisposable (void) {
		//
	}

	virtual void
	dispose (void) = 0;
};

}

#endif
