#include "logging.h"

#include <cstdarg>
#include <cstdio>

#include <SDL2/SDL_error.h>

#define DEFINE_LOG_IMPLEMENTATION(category, color_code) \
    void log_##category(const char* format, ...) \
    { \
        std::va_list args; \
        va_start(args, format); \
        std::fprintf(stderr, color_code); \
        std::vfprintf(stderr, format, args); \
        std::fprintf(stderr, "\x1b[0m\n"); \
        va_end(args); \
    }

DEFINE_LOG_IMPLEMENTATION(warning, "\x1b[1;33m")
DEFINE_LOG_IMPLEMENTATION(error, "\x1b[1;31m")

void log_sdl_error()
{
    log_error("SDL error: %s", SDL_GetError());
}
