#include <SDL.h>
#include <SDL_opengles.h>

#include <IGame.h>

#ifndef SDL_Application_h
#define SDL_Application_h

class SDL_Application {
public:
	SDL_Application ();

	void run (IGame &game);

	virtual ~SDL_Application ();

private:
	SDL_Window *window;
	SDL_GLContext context;
	SDL_DisplayMode mode;

	int sdl_status;
	int glew_status;

};

#endif
