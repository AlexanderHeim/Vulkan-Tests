#include <vulkan/vulkan.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "suitability_checks.h"
#include "debug_utilities.h"

int main() {
	//Check if Vulkan 1.2.x is available
	if (is_vulkan_version_supported(1, 2, 0) == false) {
		printf("Vulkan version is not supported!");
		return EXIT_FAILURE;
	}
	//Check if VK_LAYER_KHRONOS_validation layer is available
	if (!is_instance_layer_available("VK_LAYER_KHRONOS_validation")) {
		printf("Validation Layer is not supported!");
		return EXIT_FAILURE;
	}
	
	//Create instance
	const VkApplicationInfo applicationInfo = {
	  .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
	  .pNext = NULL,
	  .pApplicationName = "VKComputeSample",
	  .applicationVersion = VK_MAKE_VERSION(0, 0, 0),
	  .pEngineName = "No Engine",
	  .engineVersion = VK_MAKE_VERSION(0, 0, 0),
	  .apiVersion = VK_MAKE_VERSION(1, 2, 0)
	};

	const VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = NULL,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = NULL,
		.ppEnabledLayerNames = NULL,
		.enabledExtensionCount = NULL,
		.ppEnabledExtensionNames = NULL,
	};

	VkInstance instance;
	VkResult instance_created = vkCreateInstance(&instanceCreateInfo, 0, &instance);
	if (instance_created != VK_SUCCESS) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}