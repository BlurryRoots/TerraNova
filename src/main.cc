
#include <iostream>
#include <string>
#include <SDL.h>

int
main (int argc, char **argv) {
	if (0 != SDL_Init (SDL_INIT_EVERYTHING)){
		std::cerr << "SDL_Init error: "
			<< SDL_GetError ()
			<< std::endl;

		return 1;
	}

	SDL_Quit();

	std::cout << "Quitting!" << std::endl;

	return 0;
}
