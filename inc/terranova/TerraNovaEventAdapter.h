#ifndef TerraNoveEventAdapter_h
#define TerraNoveEventAdapter_h

#include <terranova/IGame.h>
#include <SDL_IEventHandler.h>

#include <terranova/IEventHandler.h>
#include <terranova/events/MouseButtonEvent.h>
#include <terranova/events/QuitEvent.h>
#include <terranova/events/UserEvent.h>

class TerraNoveEventAdapter
: public SDL_IEventHandler {

public:
	TerraNoveEventAdapter (terranova::IEventHandler *handler)
	: handler (handler) {
		//
	}

	void
	on (const SDL_ControllerAxisEvent &event) {
		auto s = std::string ("Controller axis event!");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_ControllerButtonEvent &event) {
		auto s = std::string ("SDL_ControllerButtonEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_ControllerDeviceEvent &event) {
		auto s = std::string ("SDL_ControllerDeviceEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_DollarGestureEvent &event) {
		auto s = std::string ("SDL_DollarGestureEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_DropEvent &event) {
		auto s = std::string ("SDL_DropEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TouchFingerEvent &event) {
		auto s = std::string ("SDL_TouchFingerEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_KeyboardEvent &event) {
		auto s = std::string ("SDL_KeyboardEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyAxisEvent &event) {
		auto s = std::string ("SDL_JoyAxisEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyBallEvent &event) {
		auto s = std::string ("SDL_JoyBallEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyHatEvent &event) {
		auto s = std::string ("SDL_JoyHatEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyButtonEvent &event) {
		auto s = std::string ("SDL_JoyButtonEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyDeviceEvent &event) {
		auto s = std::string ("SDL_JoyDeviceEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MouseMotionEvent &event) {
		auto s = std::string ("SDL_MouseMotionEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MouseButtonEvent &event) {
		auto s = std::string ("SDL_MouseButtonEvent");
		SDL_Log (s.c_str ());

		auto e = terranova::MouseButtonEvent ();
		e.down = SDL_PRESSED == event.state;
		e.x = event.x;
		e.y = event.y;

		this->handler->on (e);
	}

	void
	on (const SDL_MouseWheelEvent &event) {
		auto s = std::string ("SDL_MouseWheelEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MultiGestureEvent &event) {
		auto s = std::string ("SDL_MultiGestureEvent");
		SDL_Log (s.c_str ());
	}

	//
	void
	on (const SDL_SysWMEvent &event) {
		auto s = std::string ("SDL_SysWMEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TextEditingEvent &event) {
		auto s = std::string ("SDL_TextEditingEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TextInputEvent &event) {
		auto s = std::string ("SDL_TextInputEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_UserEvent &event) {
		auto s = std::string ("SDL_UserEvent");
		SDL_Log (s.c_str ());

		// TODO: should this really be used by anything?
		uint32_t ticks =
			*static_cast<uint32_t*> (event.data1);
		void* data = event.data2;

		this->handler->on (
			terranova::UserEvent {
				event.type,
				ticks,
				data
			}
		);
	}

	void
	on (const SDL_WindowEvent &event) {
		auto s = std::string ("SDL_WindowEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_QuitEvent &event) {
		this->handler->on (
			terranova::QuitEvent {event.timestamp}
		);
	}

private:
	terranova::IEventHandler *handler;

};

#endif
