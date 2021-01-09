#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool is_vulkan_version_supported(uint32_t major, uint32_t minor, uint32_t patch) {
	uint32_t actual_version = 0;
	if (vkEnumerateInstanceVersion(&actual_version) != VK_SUCCESS) {
		return false;
	}
	if ((major != VK_VERSION_MAJOR(actual_version)) || (minor > VK_VERSION_MINOR(actual_version))) {
		return false;
	}
	return true;
}

bool is_instance_layer_available(char* layer_name) {
	uint32_t propertyCount;
	vkEnumerateInstanceLayerProperties(&propertyCount, NULL);
	VkLayerProperties* properties = (VkLayerProperties*) calloc(propertyCount, sizeof(VkLayerProperties));
	vkEnumerateInstanceLayerProperties(&propertyCount, properties);
	if (properties == NULL) {
		free(properties);
		return false;
	}
	for (int i = 0; i < propertyCount; i++) {
		if (strcmp(layer_name, properties[i].layerName) == 0) {
			free(properties);
			return true;
		}
	}
	free(properties);
	return false;
}

bool is_instance_extension_available_nolayer(char* extension_name) {
	uint32_t propertyCount;
	vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, NULL);
	VkExtensionProperties* properties = (VkExtensionProperties*)calloc(propertyCount, sizeof(VkExtensionProperties));
	vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, properties);
	if (properties == NULL) {
		free(properties);
		return false;
	}
	for (int i = 0; i < propertyCount; i++) {
		if (strcmp(extension_name, properties[i].extensionName) == 0) {
			free(properties);
			return true;
		}
	}
	free(properties);
	return false;
}

bool is_physical_device_suitable(VkPhysicalDevice physical_device) {
	return true;
}