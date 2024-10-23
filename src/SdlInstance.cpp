#include "SdlInstance.h"

#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

#include "logging.h"

SdlInstance::SdlInstance(Uint32 flags)
{
    if (SDL_Init(flags) < 0)
    {
        log_sdl_error();
        throw std::runtime_error("Failed to initialize SDL library");
    }
}

SdlInstance::~SdlInstance()
{
    SDL_Quit();
}
