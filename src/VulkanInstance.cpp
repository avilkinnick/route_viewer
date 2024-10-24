#include "VulkanInstance.h"

#include <cstdint>

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include <vulkan/vulkan_core.h>

#include "logging.h"

#include "aliases/CExtensionName.h"
#include "aliases/CExtensionNameVector.h"
#include "aliases/CLayerName.h"
#include "aliases/CLayerNameVector.h"
#include "aliases/ExtensionMap.h"
#include "aliases/ExtensionNameViewSet.h"
#include "aliases/LayerNameSet.h"
#include "aliases/LayerNameView.h"
#include "aliases/LayerNameViewSet.h"

#define VK_LAYER_KHRONOS_VALIDATION_LAYER_NAME "VK_LAYER_KHRONOS_validation"

VulkanInstance::VulkanInstance(
    const char* application_name,
    std::uint32_t application_version,
    const CExtensionNameVector&& window_required_extension_names
)
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

    const auto available_layer_names = get_available_layer_names();
    const auto available_extensions = get_available_extensions(available_layer_names);

    LayerNameViewSet enabled_layer_name_set;
    ExtensionNameViewSet enabled_extension_name_set;

    enable_extensions(
        enabled_layer_name_set,
        enabled_extension_name_set,
        available_extensions,
        window_required_extension_names,
        [](const char* window_required_extension_name) {
            throw std::runtime_error(
                std::string("Required Vulkan instance extension ")
                + window_required_extension_name
                + " is not available"
            );
        }
    );

#ifndef NDEBUG
    const CLayerNameVector optional_layer_names = {VK_LAYER_KHRONOS_VALIDATION_LAYER_NAME};
    const CExtensionNameVector optional_extension_names = {
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME
    };
#else
    const CLayerNameVector optional_layer_names;
    const CExtensionNameVector optional_extension_names = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME};
#endif

    enable_optional_layers(enabled_layer_name_set, available_layer_names, optional_layer_names);

    enable_extensions(
        enabled_layer_name_set,
        enabled_extension_name_set,
        available_extensions,
        optional_extension_names,
        [](const char* optional_extension_name) {
            log_warning("Optional Vulkan instance extension %s is not available", optional_extension_name);
        }
    );

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

LayerNameSet VulkanInstance::get_available_layer_names() const
{
    std::uint32_t available_layer_count;
    vkEnumerateInstanceLayerProperties(&available_layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers_properties(available_layer_count);
    vkEnumerateInstanceLayerProperties(&available_layer_count, available_layers_properties.data());

    LayerNameSet available_layer_names;
    for (const auto& available_layer_properties : available_layers_properties)
    {
        available_layer_names.emplace(available_layer_properties.layerName);
    }

    return available_layer_names;
}

ExtensionMap VulkanInstance::get_available_extensions(const LayerNameSet& available_layer_names) const
{
    ExtensionMap available_extensions;
    get_available_extensions_from_layer(available_extensions);

    for (LayerNameView available_layer_name : available_layer_names)
    {
        get_available_extensions_from_layer(available_extensions, available_layer_name);
    }

    return available_extensions;
}

void VulkanInstance::get_available_extensions_from_layer(
    ExtensionMap& available_extensions,
    std::optional<LayerNameView> layer_name
) const
{
    std::uint32_t available_extension_count;
    vkEnumerateInstanceExtensionProperties(
        layer_name ? layer_name->data() : nullptr,
        &available_extension_count,
        nullptr
    );

    std::vector<VkExtensionProperties> available_extensions_properties(available_extension_count);
    vkEnumerateInstanceExtensionProperties(
        layer_name ? layer_name->data() : nullptr,
        &available_extension_count,
        available_extensions_properties.data()
    );

    for (const auto& available_extension_properties : available_extensions_properties)
    {
        available_extensions.emplace(available_extension_properties.extensionName, layer_name);
    }
}

void VulkanInstance::enable_extensions(
    LayerNameViewSet& enabled_layer_name_set,
    ExtensionNameViewSet& enabled_extension_name_set,
    const ExtensionMap& available_extensions,
    const CExtensionNameVector& required_extension_names,
    std::function<void(const char* required_extension_name)> on_extension_unavailable
) const
{
    for (CExtensionName required_extension_name : required_extension_names)
    {
        const auto found_extension_iterator = available_extensions.find(required_extension_name);
        if (found_extension_iterator == available_extensions.cend())
        {
            on_extension_unavailable(required_extension_name);
        }
        else
        {
            enabled_extension_name_set.emplace(found_extension_iterator->first);
            if (found_extension_iterator->second)
            {
                enabled_layer_name_set.emplace(*found_extension_iterator->second);
            }
        }
    }
}

void VulkanInstance::enable_optional_layers(
    LayerNameViewSet& enabled_layer_name_set,
    const LayerNameSet& available_layer_names,
    const CLayerNameVector& optional_layer_names
) const
{
    for (CLayerName optional_layer_name : optional_layer_names)
    {
        if (available_layer_names.find(optional_layer_name) == available_layer_names.end())
        {
            log_warning("Optional Vulkan instance layer %s is not available", optional_layer_name);
        }
        else
        {
            enabled_layer_name_set.emplace(optional_layer_name);
        }
    }
}
