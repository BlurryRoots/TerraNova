#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengles.h>

#include <IGame.h>

#ifndef SDL_Application_h
#define SDL_Application_h

class SDL_Application {
public:
	SDL_Application () {
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

	template<class GameType> int
	run_with () {
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
			// sld event container
			SDL_Event e;
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

				// map sdl events and passed them to the game
				while (SDL_PollEvent (&e)) {
					switch (e.type) {
						case SDL_QUIT:
							game.on_shutdown_request ();
							break;
					}
				}

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
	~SDL_Application () {
		if (0 < this->sdl_status) {
			SDL_GL_DeleteContext (context);
			SDL_DestroyWindow (window);
		}

		SDL_Quit ();
	}

private:
	SDL_Window *window;
	SDL_GLContext context;
	SDL_DisplayMode mode;

	int sdl_status;
	int glew_status;

};

#endif
