#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_stdinc.h>

struct SDL_Window;

class Window
{
public:
    Window(const char* title, int x, int y, int width, int height, Uint32 flags);
    Window(const char* title, int width, int height, Uint32 flags);
    ~Window();

private:
    SDL_Window* window;
};

#endif // WINDOW_H
