#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

class SdlInstance;
class VulkanInstance;
class Window;

class Application
{
public:
    Application();
    ~Application();

    void initialize();
    void run();

private:
    std::unique_ptr<const SdlInstance> sdl_instance;
    std::unique_ptr<const Window> window;
    std::unique_ptr<const VulkanInstance> vulkan_instance;
};

#endif // APPLICATION_H
