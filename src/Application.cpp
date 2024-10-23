#include "Application.h"

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>

#include "SdlInstance.h"
#include "Window.h"

Application::Application() = default;
Application::~Application() = default;

void Application::initialize()
{
    sdl_instance = std::make_unique<SdlInstance>(SDL_INIT_VIDEO);
    window = std::make_unique<Window>("Route Viewer", 800, 600, SDL_WINDOW_VULKAN);
}

void Application::run()
{
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
                break;
            }
        }
    }
}
