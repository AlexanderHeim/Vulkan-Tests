#ifndef VULKAN_UTILITIES
#define VULKAN_UTILITIES

#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>

//Picks the best suitable physical device available (using a score system)
VkPhysicalDevice pick_best_physical_device(VkInstance instance);


#endif