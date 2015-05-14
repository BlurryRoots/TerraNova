#ifndef SDL_Application_h
#define SDL_Application_h

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengles.h>

#include <IGame.h>

template<class GameType>
class SDL_Application {
public:
	SDL_Application (void) {
		SDL_Log ("Launching application...");

		this->sdl_status = SDL_Init (SDL_INIT_EVERYTHING);
		if (0 > this->sdl_status) {
			SDL_Log ("Unable to initialize SDL");
		}
		else {
			SDL_Log ("SDL initialized...");
			SDL_GetDesktopDisplayMode (0, &(this->mode));

			SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 16);
			SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 1);

			SDL_Log ("Creating window...");
			// Create our window centered
			this->window = SDL_CreateWindow ("GLES example",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				//mode.w, mode.h,
				800, 600,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
			);

			SDL_Log ("Creating context...");
			// Create our opengl context and attach it to our window
			this->context = SDL_GL_CreateContext (this->window);
			SDL_GL_MakeCurrent (this->window, this->context);

			SDL_GL_SetSwapInterval (1);

			// Extension wrangler initialising
			glewExperimental = GL_TRUE;
			this->glew_status = glewInit ();
		}
	}

	int
	run (void) {
		if (GLEW_OK != this->glew_status) {
			std::cout << "Could not initialize glew!" << std::endl;
			return 1;
		}

		int status = 0;
		SDL_Log ("Running game...");
		try {
			// game initialization should be done in constructor
			// if something fails here, the user has to make sure
			// his mess gets clean up by the integral parts
			// see http://stackoverflow.com/a/810850/949561
			GameType game;
			// no use for this atm
			bool keep_running = true;
			// keeps track of the ticks of last from
			Uint32 last_ticks = SDL_GetTicks ();

			// application loop
			while (keep_running
				&& ! game.has_closing_request ()) {
				// calculate time passed since last frame
				Uint32 current_ticks = SDL_GetTicks ();
				Uint32 diff_ticks = current_ticks - last_ticks;
				float dt = static_cast<float> (diff_ticks) / 1000.0f;

				// custom game logic
				game.on_update (dt);

				this->process_sdl_events (game);

				// custome game render logic
				game.on_render ();
				// swap window buffer
				SDL_GL_SwapWindow (window);

				// update last frame time
				last_ticks = current_ticks;
			}

			// gets called when game loop is successfully exited
			game.on_shutdown ();
		}
		catch (std::exception &ex) {
			std::cout << "Cought: " << ex.what () << std::endl;
			status = 22;
		}
		catch (...) {
			std::cout << "Cought unkown exception :(" << std::endl;
			status = 23;
		}

		return status;
	}

	virtual
	~SDL_Application (void) {
		if (0 < this->sdl_status) {
			SDL_GL_DeleteContext (context);
			SDL_DestroyWindow (window);
		}

		SDL_Quit ();
	}

private:
	void
	process_sdl_events (GameType &game) {
		// sld event container
		SDL_Event e;

		// map sdl events and passed them to the game
		while (SDL_PollEvent (&e)) {
			switch (e.type) {
				case SDL_CONTROLLERAXISMOTION:
					this->on (e.caxis, game);
					break;
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP:
					this->on (e.cbutton, game);
					break;
				case SDL_CONTROLLERDEVICEADDED:
				case SDL_CONTROLLERDEVICEREMOVED:
				case SDL_CONTROLLERDEVICEREMAPPED:
					this->on (e.cdevice, game);
					break;
				case SDL_DOLLARGESTURE:
				case SDL_DOLLARRECORD:
					this->on (e.dgesture, game);
					break;
				case SDL_DROPFILE:
					this->on (e.drop, game);
					break;
				case SDL_FINGERMOTION:
				case SDL_FINGERDOWN:
				case SDL_FINGERUP:
					this->on (e.tfinger, game);
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					this->on (e.key, game);
					break;
				case SDL_JOYAXISMOTION:
					this->on (e.jaxis, game);
					break;
				case SDL_JOYBALLMOTION:
					this->on (e.jball, game);
					break;
				case SDL_JOYHATMOTION:
					this->on (e.jhat, game);
					break;
				case SDL_JOYBUTTONDOWN:
				case SDL_JOYBUTTONUP:
					this->on (e.jbutton, game);
					break;
				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:
					this->on (e.jdevice, game);
					break;
				case SDL_MOUSEMOTION:
					this->on (e.motion, game);
					break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					this->on (e.button, game);
					break;
				case SDL_MOUSEWHEEL:
					this->on (e.wheel, game);
					break;
				case SDL_MULTIGESTURE:
					this->on (e.mgesture, game);
					break;
				case SDL_QUIT:
					this->on (e.quit, game);
					break;
				case SDL_SYSWMEVENT:
					this->on (e.syswm, game);
					break;
				case SDL_TEXTEDITING:
					this->on (e.edit, game);
					break;
				case SDL_TEXTINPUT:
					this->on (e.text, game);
					break;
				case SDL_USEREVENT:
					this->on (e.user, game);
					break;
				case SDL_WINDOWEVENT:
					this->on (e.window, game);
					break;
				default:
					SDL_Log ("Panic! Unkown event!");
					break;
			}
		}
	}

	void
	on (const SDL_ControllerAxisEvent &event, GameType &game) {
		auto s = std::string ("Controller axis event!");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_ControllerButtonEvent &event, GameType &game) {
		auto s = std::string ("SDL_ControllerButtonEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_ControllerDeviceEvent &event, GameType &game) {
		auto s = std::string ("SDL_ControllerDeviceEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_DollarGestureEvent &event, GameType &game) {
		auto s = std::string ("SDL_DollarGestureEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_DropEvent &event, GameType &game) {
		auto s = std::string ("SDL_DropEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TouchFingerEvent &event, GameType &game) {
		auto s = std::string ("SDL_TouchFingerEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_KeyboardEvent &event, GameType &game) {
		auto s = std::string ("SDL_KeyboardEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyAxisEvent &event, GameType &game) {
		auto s = std::string ("SDL_JoyAxisEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyBallEvent &event, GameType &game) {
		auto s = std::string ("SDL_JoyBallEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyHatEvent &event, GameType &game) {
		auto s = std::string ("SDL_JoyHatEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyButtonEvent &event, GameType &game) {
		auto s = std::string ("SDL_JoyButtonEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_JoyDeviceEvent &event, GameType &game) {
		auto s = std::string ("SDL_JoyDeviceEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MouseMotionEvent &event, GameType &game) {
		auto s = std::string ("SDL_MouseMotionEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MouseButtonEvent &event, GameType &game) {
		auto s = std::string ("SDL_MouseButtonEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MouseWheelEvent &event, GameType &game) {
		auto s = std::string ("SDL_MouseWheelEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_MultiGestureEvent &event, GameType &game) {
		auto s = std::string ("SDL_MultiGestureEvent");
		SDL_Log (s.c_str ());
	}

	//
	void
	on (const SDL_SysWMEvent &event, GameType &game) {
		auto s = std::string ("SDL_SysWMEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TextEditingEvent &event, GameType &game) {
		auto s = std::string ("SDL_TextEditingEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_TextInputEvent &event, GameType &game) {
		auto s = std::string ("SDL_TextInputEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_UserEvent &event, GameType &game) {
		auto s = std::string ("SDL_UserEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_WindowEvent &event, GameType &game) {
		auto s = std::string ("SDL_WindowEvent");
		SDL_Log (s.c_str ());
	}

	void
	on (const SDL_QuitEvent &event, GameType &game) {
		auto s = std::string ("Quitting event! at: ")
			+ std::to_string (event.timestamp / 1000.0f);
		SDL_Log (s.c_str ());

		game.on_shutdown_request ();
	}

	SDL_Window *window;
	SDL_GLContext context;
	SDL_DisplayMode mode;

	int sdl_status;
	int glew_status;

};

#endif
