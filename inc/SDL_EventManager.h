#ifndef SDL_EventManager_h
#define SDL_EventManager_h

#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include <SDL.h>

#include <SDL_IEventHandler.h>
#include <terranova/events/UserEvent.h>

#include <blurryroots/throwif.h>

class SDL_EventManager {

public:
	SDL_EventManager (SDL_EventHandler *handler)
	: handler (handler) {
		//
	}

	virtual
	~SDL_EventManager (void) {
		//
	}

	// TODO: this should not be in the sdl side of things!!
	template<class TEventType> void
	push (TEventType *event) {
		auto type_name = typeid (TEventType).name ();
		auto event_id_it = this->user_event_ids.find (type_name);

		if (this->user_event_ids.end () == event_id_it) {
			Uint32 new_event_type_id = SDL_RegisterEvents (1);
			THROW_IF (((Uint32)-1) == new_event_type_id,
				"Error creating user event type id!"
			);

			this->user_event_ids.emplace (type_name, new_event_type_id);
		}

		// create heap ticks
		Uint32 *ticks = new Uint32;
		*ticks = SDL_GetTicks ();
		// create sdl event structure
		SDL_Event sdl_event;
		// initialize the event with zero values
		SDL_zero (sdl_event);
		sdl_event.type = this->user_event_ids.at (type_name);
		sdl_event.user.code = 1337;
		sdl_event.user.data1 = static_cast<void*> (ticks);
		sdl_event.user.data2 = static_cast<void*> (event);
		SDL_PushEvent (&sdl_event);
	}

	void
	process (SDL_Event &e) {
		switch (e.type) {
			case SDL_CONTROLLERAXISMOTION:
				this->handler->on (e.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				this->handler->on (e.cbutton);
				break;
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
				this->handler->on (e.cdevice);
				break;
			case SDL_DOLLARGESTURE:
			case SDL_DOLLARRECORD:
				this->handler->on (e.dgesture);
				break;
			case SDL_DROPFILE:
				this->handler->on (e.drop);
				break;
			case SDL_FINGERMOTION:
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				this->handler->on (e.tfinger);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				this->handler->on (e.key);
				break;
			case SDL_JOYAXISMOTION:
				this->handler->on (e.jaxis);
				break;
			case SDL_JOYBALLMOTION:
				this->handler->on (e.jball);
				break;
			case SDL_JOYHATMOTION:
				this->handler->on (e.jhat);
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				this->handler->on (e.jbutton);
				break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				this->handler->on (e.jdevice);
				break;
			case SDL_MOUSEMOTION:
				this->handler->on (e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				this->handler->on (e.button);
				break;
			case SDL_MOUSEWHEEL:
				this->handler->on (e.wheel);
				break;
			case SDL_MULTIGESTURE:
				this->handler->on (e.mgesture);
				break;
			case SDL_QUIT:
				this->handler->on (e.quit);
				break;
			case SDL_SYSWMEVENT:
				this->handler->on (e.syswm);
				break;
			case SDL_TEXTEDITING:
				this->handler->on (e.edit);
				break;
			case SDL_TEXTINPUT:
				this->handler->on (e.text);
				break;
			case SDL_USEREVENT:
				this->handler->on (e.user);
				break;
			case SDL_WINDOWEVENT:
				this->handler->on (e.window);
				break;
			default:
				SDL_Log ("Panic! Unkown event!");
				break;
		}
	}

private:
	SDL_EventHandler *handler;
	std::unordered_map<std::string, Uint32> user_event_ids;

};

#endif
