#include <vulkan/vulkan.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "suitability_checks.h"
#include "debug_utilities.h"


//DESTROYING INSTANCE AND STUFF STILL NEEDS TO BE IMPLEMENTED
int main() {
	const char* layernames[1] = { "VK_LAYER_KHRONOS_validation" };
	const char* extensionnames[1] = { "VK_EXT_debug_utils" };

	//Check if Vulkan 1.2.x is available
	if (is_vulkan_version_supported(1, 2, 0) == false) {
		printf("Vulkan version is not supported!");
		return EXIT_FAILURE;
	}
	//Check if layer is available
	if (!is_instance_layer_available(layernames[0])) {
		printf("Validation Layer is not supported!");
		return EXIT_FAILURE;
	}
	//Check if extensions are available
	if (!is_instance_extension_available_nolayer(extensionnames[0])) {
		printf("Extension Layer is not supported!");
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

	VkDebugUtilsMessengerCreateInfoEXT debugCreateinfo = {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.flags = NULL,
		.pNext = NULL,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pUserData = NULL,
		.pfnUserCallback = debugCallback,
	};

	const VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = &debugCreateinfo,
		.flags = NULL,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = 1,
		.ppEnabledLayerNames = &layernames,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = &extensionnames,
	};


	VkInstance instance;
	VkResult instance_created = vkCreateInstance(&instanceCreateInfo, 0, &instance);
	if (instance_created != VK_SUCCESS) {
		return EXIT_FAILURE;
	}
	printf("Instance created!");

	//Get Pointer to extension function
	PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessenger = vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	
	//Actually create the debug messenger
	VkDebugUtilsMessengerEXT debug = 0;
	createDebugUtilsMessenger(instance, &debugCreateinfo, NULL, &debug);
	return EXIT_SUCCESS;
}

