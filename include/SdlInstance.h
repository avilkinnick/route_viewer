#ifndef SDL_INSTANCE_H
#define SDL_INSTANCE_H

#include <SDL2/SDL_stdinc.h>

class SdlInstance
{
public:
    explicit SdlInstance(Uint32 flags);
    ~SdlInstance();
};

#endif // SDL_INSTANCE_H
