#ifndef SDL_EventManager_h
#define SDL_EventManager_h

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

#include <SDL.h>

#include <SDL_IEventHandler.h>
#include <terranova/IEventManager.h>
#include <terranova/events/UserEvent.h>

#include <blurryroots/throwif.h>

class SDL_EventManager {

public:
	SDL_EventManager () {
		//
	}

	virtual
	~SDL_EventManager (void) {
		//
	}

	void
	add_handler (SDL_IEventHandler *handler) {
		this->handlers.emplace (handler);
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
		// add event to event queue
		SDL_PushEvent (&sdl_event);
	}

	void
	process (SDL_Event &e) {
		for (auto handler :	 this->handlers) {
		switch (e.type) {
			case SDL_CONTROLLERAXISMOTION:
				handler->on (e.caxis);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				handler->on (e.cbutton);
				break;
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
				handler->on (e.cdevice);
				break;
			case SDL_DOLLARGESTURE:
			case SDL_DOLLARRECORD:
				handler->on (e.dgesture);
				break;
			case SDL_DROPFILE:
				handler->on (e.drop);
				break;
			case SDL_FINGERMOTION:
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				handler->on (e.tfinger);
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handler->on (e.key);
				break;
			case SDL_JOYAXISMOTION:
				handler->on (e.jaxis);
				break;
			case SDL_JOYBALLMOTION:
				handler->on (e.jball);
				break;
			case SDL_JOYHATMOTION:
				handler->on (e.jhat);
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				handler->on (e.jbutton);
				break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
				handler->on (e.jdevice);
				break;
			case SDL_MOUSEMOTION:
				handler->on (e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handler->on (e.button);
				break;
			case SDL_MOUSEWHEEL:
				handler->on (e.wheel);
				break;
			case SDL_MULTIGESTURE:
				handler->on (e.mgesture);
				break;
			case SDL_QUIT:
				handler->on (e.quit);
				break;
			case SDL_SYSWMEVENT:
				handler->on (e.syswm);
				break;
			case SDL_TEXTEDITING:
				handler->on (e.edit);
				break;
			case SDL_TEXTINPUT:
				handler->on (e.text);
				break;
			case SDL_USEREVENT:
				handler->on (e.user);
				break;
			case SDL_WINDOWEVENT:
				handler->on (e.window);
				break;
			default:
				SDL_Log ("Panic! Unkown event! (%s)",
					std::to_string (e.type).c_str ()
				);
				break;
		}
		}
	}

private:
	std::unordered_map<std::string, Uint32> user_event_ids;
	std::unordered_set<SDL_IEventHandler*> handlers;
};

#endif
