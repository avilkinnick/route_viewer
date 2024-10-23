#include "VulkanInstance.h"

#include <cstdint>

#include <vulkan/vulkan_core.h>

VulkanInstance::VulkanInstance(const char* application_name, std::uint32_t application_version)
{
    std::uint32_t api_version;
    vkEnumerateInstanceVersion(&api_version);

    VkApplicationInfo application_info;
    application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pNext = nullptr;
    application_info.pApplicationName = application_name;
    application_info.applicationVersion = application_version;
    application_info.pEngineName = nullptr;
    application_info.engineVersion = 0;
    application_info.apiVersion = api_version;

    VkInstanceCreateInfo create_info;
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // create_info.pNext;
    // create_info.flags;
    create_info.pApplicationInfo = &application_info;
    // create_info.enabledLayerCount;
    // create_info.ppEnabledLayerNames;
    // create_info.enabledExtensionCount;
    // create_info.ppEnabledExtensionNames;
}
