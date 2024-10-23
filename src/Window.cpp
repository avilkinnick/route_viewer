#include "Window.h"

#include <stdexcept>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include "logging.h"

Window::Window(const char* title, int x, int y, int width, int height, Uint32 flags)
{
    window = SDL_CreateWindow(title, x, y, width, height, flags);
    if (!window)
    {
        log_sdl_error();
        throw std::runtime_error("Failed to create SDL window");
    }
}

Window::Window(const char* title, int width, int height, Uint32 flags)
    : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)
{
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}
