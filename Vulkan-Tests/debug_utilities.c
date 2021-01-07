#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>


void print_available_instance_layers() {
	uint32_t propertyCount;
	vkEnumerateInstanceLayerProperties(&propertyCount, NULL);
	VkLayerProperties* properties = (VkLayerProperties*) calloc(propertyCount, sizeof(VkLayerProperties));
	vkEnumerateInstanceLayerProperties(&propertyCount, properties);
	if (properties == NULL) {
		printf("ERROR: VkLayerProperties* properties is a NULL-Pointer!");
		free(properties);
		return;
	}
	for (int i = 0; i < propertyCount; i++) {
		printf("%s\n", properties[i].layerName);
	}
	free(properties);
}