#ifndef DEBUG_UTILITIES
#define DEBUG_UTILITIES

#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>

VkBool32 VKAPI_PTR debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData);

void print_available_instance_layers();

//Doesnt take layer into account
void print_available_instance_extensions_nolayers();


#endif