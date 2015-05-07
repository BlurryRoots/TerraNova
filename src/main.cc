#include <SDL_Application.h>
#include <TerraNovaGame.h>

int
main (int argc, char **argv) {
	// run the game via sdl
	return SDL_Application ().run_with<TerraNovaGame> ();
}
