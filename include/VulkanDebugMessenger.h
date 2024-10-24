#ifndef VULKAN_DEBUG_MESSENGER_H
#define VULKAN_DEBUG_MESSENGER_H

#include <vulkan/vulkan_core.h>

class VulkanDebugMessenger
{
public:
    VulkanDebugMessenger(VkInstance vulkan_instance, const VkDebugUtilsMessengerCreateInfoEXT* create_info);
    ~VulkanDebugMessenger();

private:
    VkInstance instance;
    VkDebugUtilsMessengerEXT messenger;
    PFN_vkDestroyDebugUtilsMessengerEXT destroy_messenger;
};

#endif // VULKAN_DEBUG_MESSENGER_H
