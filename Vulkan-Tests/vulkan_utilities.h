#ifndef VULKAN_UTILITIES
#define VULKAN_UTILITIES

#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>

#define NO_INDEX_PRESENT 4294967199

typedef struct QueueFamilyIndices {
	uint32_t graphicsFamily;
} QueueFamilyIndices;

QueueFamilyIndices find_queue_families(VkPhysicalDevice physical_device);
//Picks the best suitable physical device available (using a score system)
VkPhysicalDevice pick_best_physical_device(VkInstance instance);


#endif