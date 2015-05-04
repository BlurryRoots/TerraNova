
#include <GL/glew.h>

#include <SDL.h>
#include <SDL2/SDL_opengles.h>

#include <iostream>
#include <string>

class IApplication {
public:
	virtual ~IApplication ()
	{}

	virtual void on_mousebutton_down (SDL_Event event) = 0;
	virtual void on_mousebutton_up (SDL_Event event) = 0;

	virtual void on_key_up (SDL_Event event) = 0;
	virtual void on_key_down (SDL_Event event) = 0;

	virtual void on_window_resize (SDL_Event event) = 0;

	virtual void on_update (Uint32 dt) = 0;

	virtual void on_render () = 0;
};

class TestApp : IApplication {

public:
	void on_mousebutton_down (SDL_Event event) {
		log ("mouse down");
	}

	void on_mousebutton_up (SDL_Event event) {
		log ("mouse up");
	}

	void on_key_up (SDL_Event event) {
		log ("key up");
	}

	void on_key_down (SDL_Event event) {
		log ("key down");
	}

	void on_window_resize (SDL_Event event) {
		log ("window resize");

		int w = event.window.data1;
		int h = event.window.data2;
		float aspectAdjust;

		aspectAdjust = (4.0f / 3.0f) / ((float)w / h);
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrthof(-2.0, 2.0, -2.0 * aspectAdjust, 2.0 * aspectAdjust, -20.0, 20.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glShadeModel(GL_SMOOTH);
	}

	void on_update (Uint32 dt) {

	}

	void on_render () {
		glClearColor (0.0, 0.0, 0.0, 1.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void log (std::string msg) {
		std::cout << msg << std::endl;
	}
};

/*
if (event.key.keysym.scancode == SDL_SCANCODE_AC_BACK)
{
	done = 1;
}
*/

int
initialize_sdl (SDL_GLContext *context, SDL_Window *window) {
	SDL_DisplayMode mode;

	if (0 > SDL_Init (SDL_INIT_EVERYTHING)) {
		SDL_Log("Unable to initialize SDL");

		return 1;
	}

	SDL_GetDesktopDisplayMode (0, &mode);

	SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 16);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 1);

	// Create our window centered
	window = SDL_CreateWindow ("GLES example",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		mode.w, mode.h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	// Create our opengl context and attach it to our window
	*context = SDL_GL_CreateContext (window);

	SDL_GL_MakeCurrent (window, *context);

	SDL_GL_SetSwapInterval (1);

	return 0;
}

void
shutdown_sdl (SDL_GLContext context, SDL_Window *window) {
	SDL_GL_DeleteContext (context);
	SDL_DestroyWindow (window);
	SDL_Quit ();
}

int
main (int argc, char **argv) {

	SDL_Window *window = nullptr;
	SDL_GLContext context;

	if (! initialize_sdl (&context, window)) {
		return 1;
	}

	// Extension wrangler initialising
	glewExperimental = GL_TRUE;
	GLuint glew_status = glewInit ();
	if (GLEW_OK != glew_status) {
		std::cout << "Could not initialize glew!" << std::endl;

		shutdown_sdl (context, window);
		return 1;
	}

	TestApp app;

	SDL_Event event;
	Uint32 then = SDL_GetTicks ();
	Uint32 now = 0;
	Uint32 frames = 0;
	int done = 0;

	while (! done) {
		app.on_update (SDL_GetTicks ());

		++frames;
		while (SDL_PollEvent (&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					app.on_key_down (event);
					break;

				case SDL_MOUSEBUTTONDOWN:
					app.on_mousebutton_down (event);
					break;

				case SDL_MOUSEBUTTONUP:
					app.on_mousebutton_up (event);
					break;

				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							SDL_GL_SwapWindow (window);
							app.on_window_resize (event);
							break;
					}
					break;
			}

		}

		app.on_render ();
		SDL_GL_SwapWindow (window);
	}

	/* Print out some timing information */
	now = SDL_GetTicks();
	if (now > then)
	{
		SDL_Log ("%2.2f frames per second\n",
			((double)frames * 1000) / (now - then)
		);
	}

	shutdown_sdl (context, window);

	return 0;
}
