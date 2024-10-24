#include "Application.h"

#include <iostream>
#include <memory>

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>

#include "logging.h"
#include "SdlInstance.h"
#include "VulkanDebugMessenger.h"
#include "VulkanInstance.h"
#include "Window.h"

Application::Application() = default;
Application::~Application() = default;

void Application::initialize()
{
    sdl_instance = std::make_unique<const SdlInstance>(SDL_INIT_VIDEO);
    window = std::make_unique<const Window>("Route Viewer", 800, 600, SDL_WINDOW_VULKAN);

    const auto debug_messenger_create_info = create_debug_messenger_create_info();

    vulkan_instance = std::make_unique<VulkanInstance>(
        "Route Viewer",
        1,
        window->get_required_vulkan_extensions(),
        &debug_messenger_create_info
    );

    vulkan_debug_messenger = std::make_unique<const VulkanDebugMessenger>(
        *vulkan_instance,
        &debug_messenger_create_info
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

VkDebugUtilsMessengerCreateInfoEXT Application::create_debug_messenger_create_info() const
{
    VkDebugUtilsMessengerCreateInfoEXT debug_messenger_create_info;
    debug_messenger_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_messenger_create_info.pNext = nullptr;
    debug_messenger_create_info.flags = 0;

    debug_messenger_create_info.messageSeverity
        = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        // | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    debug_messenger_create_info.messageType
        = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;

    debug_messenger_create_info.pfnUserCallback = [](
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
        VkDebugUtilsMessageTypeFlagsEXT message_types,
        const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
        void* user_data
    )
    {
        switch (message_severity)
        {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            std::cout << callback_data->pMessage << '\n';
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            log_warning(callback_data->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            log_error(callback_data->pMessage);
            break;
        default:
            break;
        }

        return VK_FALSE;
    };

    debug_messenger_create_info.pUserData = nullptr;

    return debug_messenger_create_info;
}
