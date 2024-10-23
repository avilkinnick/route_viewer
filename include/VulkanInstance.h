#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include <cstdint>

#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>

#include <vulkan/vulkan_core.h>

class VulkanInstance
{
private:
    using CLayerName = const char*;
    using LayerName = std::string;
    using LayerNameView = std::string_view;
    using LayerNameSet = std::set<LayerName>;

    using CExtensionName = const char*;
    using ExtensionName = std::string;
    using ExtensionMap = std::map<ExtensionName, std::optional<LayerNameView>>;

public:
    VulkanInstance(const char* application_name, std::uint32_t application_version);

private:
    LayerNameSet get_available_layer_names() const;
    ExtensionMap get_available_extensions(const LayerNameSet& available_layer_names) const;

    void get_available_extensions_from_layer(
        ExtensionMap& available_extensions,
        std::optional<LayerNameView> layer_name = std::nullopt
    ) const;

private:
    VkInstance instance;
};

#endif // VULKAN_INSTANCE_H
