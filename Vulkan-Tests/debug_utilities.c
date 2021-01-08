#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>


VkBool32 VKAPI_PTR debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
	printf("%s\n", pCallbackData->pMessage);
	return VK_FALSE;
}


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

void print_available_instance_extensions_nolayers() {
	uint32_t extensionCount;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* properties = (VkExtensionProperties*)calloc(extensionCount, sizeof(VkExtensionProperties));
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, properties);
	if (properties == NULL) {
		printf("ERROR: VkExtensionProperties* properties is a NULL-Pointer!");
		free(properties);
		return;
	}
	for (int i = 0; i < extensionCount; i++) {
		printf("%s\n", properties[i].extensionName);
	}
	free(properties);
}