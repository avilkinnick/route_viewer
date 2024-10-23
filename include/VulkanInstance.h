#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include <cstdint>

#include <optional>

#include <vulkan/vulkan_core.h>

#include "aliases/ExtensionMap.h"
#include "aliases/LayerNameSet.h"
#include "aliases/LayerNameView.h"

class VulkanInstance
{
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
