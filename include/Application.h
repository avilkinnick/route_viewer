#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include <vulkan/vulkan_core.h>

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
    VkDebugUtilsMessengerCreateInfoEXT create_debug_messenger_create_info() const;

private:
    std::unique_ptr<const SdlInstance> sdl_instance;
    std::unique_ptr<const Window> window;
    std::unique_ptr<const VulkanInstance> vulkan_instance;
};

#endif // APPLICATION_H
