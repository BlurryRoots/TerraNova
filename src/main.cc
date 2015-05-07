#include <SDL_Application.h>
#include <TerraNovaGame.h>

int
main (int argc, char **argv) {
	TerraNovaGame game;

	SDL_Application application;
	application.run (game);

	return 0;
}
