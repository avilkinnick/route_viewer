#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include <cstdint>

#include <vulkan/vulkan_core.h>

class VulkanInstance
{
public:
    VulkanInstance(const char* application_name, std::uint32_t application_version);

private:
    VkInstance instance;
};

#endif // VULKAN_INSTANCE_H
