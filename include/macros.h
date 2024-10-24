#define DEFINE_VULKAN_INSTANCE_FUNCTION_POINTER(instance, function_name) \
    auto function_name = (PFN_##function_name)(vkGetInstanceProcAddr(instance, #function_name)); \
    if (!function_name) \
    { \
        throw std::runtime_error("Failed to get address of Vulkan procedure " #function_name); \
    }
