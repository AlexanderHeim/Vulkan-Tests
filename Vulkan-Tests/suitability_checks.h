#ifndef SUITABILITY_CHECKS
#define SUITABILITY_CHECKS

#include <stdint.h>
#include <stdbool.h>

bool is_vulkan_version_supported(uint32_t major, uint32_t minor, uint32_t patch);
bool is_instance_layer_available(char* layer_name);
bool is_instance_extension_available_nolayer(char* extension_name);

#endif