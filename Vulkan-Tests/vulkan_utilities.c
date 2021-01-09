#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdio.h>
#include "suitability_checks.h"
#include <stdbool.h>

VkPhysicalDevice pick_best_physical_device(VkInstance instance) {
	uint32_t physicalDeviceCount;
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
	VkPhysicalDevice* devices = (VkPhysicalDevice*)calloc(physicalDeviceCount, sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices);

	if (devices == NULL) {
		printf("ERROR: VkPhysicalDevice* devices is a NULL-POINTER!");
		free(devices);
		return NULL;
	}

	uint32_t* scores = (uint32_t*)calloc(physicalDeviceCount, sizeof(uint32_t));
	if (scores == NULL) {
		printf("ERROR: uint32_t* scores is a NULL-POINTER!");
		free(devices);
		free(scores);
		return NULL;
	}
	//give scores
	for (int i = 0; i < physicalDeviceCount; i++) {
		if (!is_physical_device_suitable(devices[i])) {
			scores[i] = 0;
			continue;
		}
		VkPhysicalDeviceProperties property;
		vkGetPhysicalDeviceProperties(devices[i], &property);

		//Give scores by device type
		switch (property.deviceType) {
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			scores[i] += 3000;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			scores[i] += 1000;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			scores[i] += 500;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			scores[i] += 100;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			scores[i] += 200;
			break;
		}
		scores[i] += property.limits.maxImageDimension2D;
	}
	//Get highest score
	uint32_t max_score_index = 0;
	for (int i = 0; i < physicalDeviceCount; i++) {
		if (scores[i] > scores[max_score_index]) {
			max_score_index = i;
		}
	}
	if (scores[max_score_index] == 0) {
		printf("COULD NOT FIND SUITABLE DEVICE!");
		free(devices);
		free(scores);
		return NULL;
	}
	VkPhysicalDevice device = devices[max_score_index];
	free(devices);
	free(scores);
	return device;
}