#ifndef TerraNove_IEventHandler_h
#define TerraNove_IEventHandler_h

#include <terranova/events/QuitEvent.h>
#include <terranova/events/UserEvent.h>
#include <terranova/events/MouseButtonEvent.h>

namespace terranova {

struct IEventHandler {

	virtual
	~IEventHandler (void) {
		//
	}

	virtual void
	on (QuitEvent e) = 0;

	virtual void
	on (UserEvent e) = 0;

	virtual void
	on (MouseButtonEvent e) = 0;

};

}

#endif
