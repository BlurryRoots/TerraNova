cmake_minimum_required (VERSION 2.8)


# sdl2
add_definitions (-DSDL_STATIC)
option (SDL_SHARED "" OFF)
add_subdirectory (sdl2)

# glew
add_definitions (-DGLEW_STATIC)
option (glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory (glew)


