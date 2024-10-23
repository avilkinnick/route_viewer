#ifndef LOGGING_H
#define LOGGING_H

void log_warning(const char* format, ...);
void log_error(const char* format, ...);
void log_sdl_error();

#endif // LOGGING_H
