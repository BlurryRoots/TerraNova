#include <iostream>
#include <string>

#include <GL/glew.h>

#include <SDL_Application.h>

SDL_Application::SDL_Application () {
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
	}

	// Extension wrangler initialising
	glewExperimental = GL_TRUE;
	this->glew_status = glewInit ();
}

void SDL_Application::run (IGame &game) {
	if (GLEW_OK != this->glew_status) {
		std::cout << "Could not initialize glew!" << std::endl;
		return;
	}

	SDL_Log ("Running game...");
	try {
		game.on_initialize ();

		SDL_Event e;
		bool keep_running = true;
		while (keep_running
			&& ! game.has_closing_request ()) {
			game.on_update (0);

			//e is an SDL_Event variable we've declared before entering the main loop
			while (SDL_PollEvent (&e)) {
				switch (e.type) {
					case SDL_QUIT:
						game.on_shutdown_request ();
						break;
				}
			}

			game.on_render ();
			SDL_GL_SwapWindow (window);
		}
	}
	catch (std::exception &ex) {
		std::cout << "Cought: " << ex.what () << std::endl;
	}
	catch (...) {
		std::cout << "Cought unkown exception :(" << std::endl;
	}

	game.on_shutdown ();
}

SDL_Application::~SDL_Application () {
	if (0 < this->sdl_status) {
		SDL_GL_DeleteContext (context);
		SDL_DestroyWindow (window);
	}

	SDL_Quit ();
}
