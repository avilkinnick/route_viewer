#ifndef ALIASES_EXTENSION_MAP_H
#define ALIASES_EXTENSION_MAP_H

#include <map>
#include <optional>

#include "ExtensionName.h"
#include "LayerNameView.h"

using ExtensionMap = std::map<ExtensionName, std::optional<LayerNameView>>;

#endif // ALIASES_EXTENSION_MAP_H
