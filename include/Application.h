#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

class SdlInstance;
class Window;

class Application
{
public:
    Application();
    ~Application();

    void initialize();
    void run();

private:
    std::unique_ptr<SdlInstance> sdl_instance;
    std::unique_ptr<Window> window;
};

#endif // APPLICATION_H
