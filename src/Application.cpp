#include "Application.h"

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>

#include "SdlInstance.h"
#include "VulkanInstance.h"
#include "Window.h"

Application::Application() = default;
Application::~Application() = default;

void Application::initialize()
{
    sdl_instance = std::make_unique<const SdlInstance>(SDL_INIT_VIDEO);
    window = std::make_unique<const Window>("Route Viewer", 800, 600, SDL_WINDOW_VULKAN);

    vulkan_instance = std::make_unique<const VulkanInstance>(
        "Route Viewer",
        1,
        window->get_required_vulkan_instance_extension_names()
    );
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
