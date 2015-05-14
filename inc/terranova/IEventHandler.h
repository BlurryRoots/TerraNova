#ifndef TerraNove_IEventHandler_h
#define TerraNove_IEventHandler_h

#include <terranova/events/QuitEvent.h>

namespace terranova {

struct IEventHandler {

	virtual
	~IEventHandler (void) {
		//
	}

	virtual void
	on (QuitEvent e) = 0;

};

}

#endif
