
#include <GL/glew.h>

#include <SDL.h>
#include <SDL2/SDL_opengles.h>

#include <iostream>
#include <string>

struct IGame {
	virtual ~IGame () {}

	virtual void on_update (float dt) = 0;
	virtual void on_render () = 0;

	virtual bool has_closing_request () = 0;
};

class TestGame
: public IGame {

public:
	void on_update (float dt) {
		this->closing_request = true;
	}

	void on_render () {
		std::cout << "Here we go!" << std::endl;
	}

	bool has_closing_request () {
		return this->closing_request;
	}

private:
	bool closing_request;

};

class SDL_Application {
public:
	SDL_Application () {
		this->sdl_status = SDL_Init (SDL_INIT_EVERYTHING);
		if (0 > this->sdl_status) {
			SDL_Log ("Unable to initialize SDL");
		}
		else {
			SDL_GetDesktopDisplayMode (0, &(this->mode));

			SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 16);
			SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 1);

			// Create our window centered
			this->window = SDL_CreateWindow ("GLES example",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				//mode.w, mode.h,
				800, 600,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
			);

			// Create our opengl context and attach it to our window
			this->context = SDL_GL_CreateContext (this->window);

			SDL_GL_MakeCurrent (this->window, this->context);

			SDL_GL_SetSwapInterval (1);
		}

		// Extension wrangler initialising
		glewExperimental = GL_TRUE;
		this->glew_status = glewInit ();
	}

	void run (IGame &game) {

		if (GLEW_OK != this->glew_status) {
			std::cout << "Could not initialize glew!" << std::endl;
			return;
		}

		SDL_Event e;
		bool keep_running = true;
		while (keep_running
			&& ! game.has_closing_request ()) {
			// update game logic
			game.on_update (0);

			//e is an SDL_Event variable we've declared before entering the main loop
			while (SDL_PollEvent (&e)) {
				switch (e.type) {
					case SDL_QUIT:
						keep_running = false;
						break;
					case SDL_MOUSEBUTTONUP:
						keep_running = false;
				}
			}

			//
			game.on_render ();
			SDL_GL_SwapWindow (window);
		}
	}

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

int
main (int argc, char **argv) {
	SDL_Application application;
	try {
		auto game = TestGame ();
		application.run (game);
	}
	catch (std::exception &ex) {
		std::cout << "Cought: " << ex.what () << std::endl;
	}
	catch (...) {
		std::cout << "Cought unkown exception :(" << std::endl;
	}

	return 0;
}
