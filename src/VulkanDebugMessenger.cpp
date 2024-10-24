#include "VulkanDebugMessenger.h"

#include <stdexcept>

#include <vulkan/vulkan_core.h>

#include "macros.h"

VulkanDebugMessenger::VulkanDebugMessenger(
    VkInstance vulkan_instance,
    const VkDebugUtilsMessengerCreateInfoEXT* create_info
)
    : instance(vulkan_instance)
{
    DEFINE_VULKAN_INSTANCE_FUNCTION_POINTER(instance, vkCreateDebugUtilsMessengerEXT)
    DEFINE_VULKAN_INSTANCE_FUNCTION_POINTER(instance, vkDestroyDebugUtilsMessengerEXT)
    destroy_messenger = vkDestroyDebugUtilsMessengerEXT;

    if (vkCreateDebugUtilsMessengerEXT(instance, create_info, nullptr, &messenger) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan debug messenger");
    }
}

VulkanDebugMessenger::~VulkanDebugMessenger()
{
    destroy_messenger(instance, messenger, nullptr);
}
