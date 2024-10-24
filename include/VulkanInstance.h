#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include <cstdint>

#include <functional>
#include <optional>

#include <vulkan/vulkan_core.h>

#include "aliases/CExtensionNameVector.h"
#include "aliases/CLayerNameVector.h"
#include "aliases/ExtensionMap.h"
#include "aliases/ExtensionNameViewSet.h"
#include "aliases/LayerNameSet.h"
#include "aliases/LayerNameView.h"
#include "aliases/LayerNameViewSet.h"

class VulkanInstance
{
public:
    VulkanInstance(
        const char* application_name,
        std::uint32_t application_version,
        const CExtensionNameVector&& window_required_extensions,
        const VkDebugUtilsMessengerCreateInfoEXT* debug_messenger_create_info
    );

    ~VulkanInstance();

    operator VkInstance() { return instance; }

private:
    LayerNameSet get_available_layer_names() const;
    ExtensionMap get_available_extensions(const LayerNameSet& available_layers) const;

    void get_available_extensions_from_layer(
        ExtensionMap& available_extensions,
        std::optional<LayerNameView> layer_name = std::nullopt
    ) const;

    void enable_extensions(
        LayerNameViewSet& enabled_layer_name_set,
        ExtensionNameViewSet& enabled_extension_name_set,
        const ExtensionMap& available_extensions,
        const CExtensionNameVector& required_extension_names,
        std::function<void(const char* required_extension_name)> on_extension_unavailable
    ) const;

    void enable_optional_layers(
        LayerNameViewSet& enabled_layer_name_set,
        const LayerNameSet& available_layer_names,
        const CLayerNameVector& optional_layer_names
    ) const;

private:
    VkInstance instance;
};

#endif // VULKAN_INSTANCE_H
