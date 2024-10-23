#include "VulkanInstance.h"

#include <cstdint>

#include <optional>
#include <string_view>
#include <vector>

#include <vulkan/vulkan_core.h>

#include "aliases/ExtensionMap.h"
#include "aliases/LayerNameSet.h"
#include "aliases/LayerNameView.h"

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

    const auto available_layer_names = get_available_layer_names();
    const auto available_extensions = get_available_extensions(available_layer_names);

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

    for (std::string_view available_layer_name : available_layer_names)
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
