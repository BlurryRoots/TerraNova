#ifndef SDL_EventManager_h
#define SDL_EventManager_h

#include <SDL.h>

#include <SDL_EventHandler.h>
#include <events/QuitEvent.h>

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

};

#endif
