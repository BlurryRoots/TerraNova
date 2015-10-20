#ifndef SDL_EventHandler_h
#define SDL_EventHandler_h

struct SDL_IEventHandler {

	virtual
	~SDL_IEventHandler (void) {
		//
	}

	virtual void
	on (const SDL_ControllerAxisEvent &event) = 0;

	virtual void
	on (const SDL_ControllerButtonEvent &event) = 0;

	virtual void
	on (const SDL_ControllerDeviceEvent &event) = 0;

	virtual void
	on (const SDL_DollarGestureEvent &event) = 0;

	virtual void
	on (const SDL_DropEvent &event) = 0;

	virtual void
	on (const SDL_TouchFingerEvent &event) = 0;

	virtual void
	on (const SDL_KeyboardEvent &event) = 0;

	virtual void
	on (const SDL_JoyAxisEvent &event) = 0;

	virtual void
	on (const SDL_JoyBallEvent &event) = 0;

	virtual void
	on (const SDL_JoyHatEvent &event) = 0;

	virtual void
	on (const SDL_JoyButtonEvent &event) = 0;

	virtual void
	on (const SDL_JoyDeviceEvent &event) = 0;

	virtual void
	on (const SDL_MouseMotionEvent &event) = 0;

	virtual void
	on (const SDL_MouseButtonEvent &event) = 0;

	virtual void
	on (const SDL_MouseWheelEvent &event) = 0;

	virtual void
	on (const SDL_MultiGestureEvent &event) = 0;

	virtual void
	on (const SDL_SysWMEvent &event) = 0;

	virtual void
	on (const SDL_TextEditingEvent &event) = 0;

	virtual void
	on (const SDL_TextInputEvent &event) = 0;

	virtual void
	on (const SDL_UserEvent &event) = 0;

	virtual void
	on (const SDL_WindowEvent &event) = 0;

	virtual void
	on (const SDL_QuitEvent &event) = 0;

};

#endif
