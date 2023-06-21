#!/usr/bin/env python3

import json
import re

ffmpeg_file = open('/tmp/ffmpeg.json', 'r')
nvidia_file = open('/tmp/nvidia.json', 'r')
ffmpeg_out = open('/tmp/ffmpeg2.json', 'w')
nvidia_out = open('/tmp/nvidia2.json', 'w')
ffmpeg_json = json.load(ffmpeg_file)
nvidia_json = json.load(nvidia_file)

names = [
    # "vkAllocateCommandBuffers",
    # "vkAllocateMemory",
    # "vkBeginCommandBuffer",
    # "vkBindBufferMemory",
    # "vkBindImageMemory",
    # "vkBindVideoSessionMemoryKHR",
    "vkCmdBeginVideoCodingKHR",
    # "vkCmdControlVideoCodingKHR",
    "vkCmdDecodeVideoKHR",
    # "vkCmdEndVideoCodingKHR",
    # "vkCmdPipelineBarrier2KHR",
    # "vkCreateBuffer",
    # "vkCreateCommandPool",
    # "vkCreateDevice",
    # "vkCreateFence",
    # "vkCreateImage",
    # "vkCreateImageView",
    # "vkCreateInstance",
    # "vkCreateSemaphore",
    "vkCreateVideoSessionKHR",
    "vkCreateVideoSessionParametersKHR",
    # "vkDestroyBuffer",
    # "vkDestroyCommandPool",
    # "vkDestroyDevice",
    # "vkDestroyFence",
    # "vkDestroyImage",
    # "vkDestroyImageView",
    # "vkDestroyInstance",
    # "vkDestroySemaphore",
    # "vkDestroyVideoSessionKHR",
    # "vkDestroyVideoSessionParametersKHR",
    # "vkEndCommandBuffer",
    # "vkEnumeratePhysicalDevices",
    # "vkFreeCommandBuffers",
    # "vkFreeMemory",
    # "vkGetBufferMemoryRequirements",
    # "vkGetDeviceQueue",
    # "vkGetFenceStatus",
    # "vkGetImageMemoryRequirements",
    # "vkGetImageSubresourceLayout",
    # "vkGetPhysicalDeviceMemoryProperties",
    # "vkGetPhysicalDeviceProperties",
    # "vkGetPhysicalDeviceProperties2",
    # "vkGetPhysicalDeviceQueueFamilyProperties2",
    # "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    # vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    # "vkGetVideoSessionMemoryRequirementsKHR",
    # "vkMapMemory",
    # "vkQueueSubmit",
    # "vkQueueWaitIdle",
    # "vkResetFences",
    # "vkUnmapMemory",
    # "vkWaitForFences",
    # "vkCmdCopyImageToBuffer",
]
interesting_calls_prg = r'|'.join(names)
interesting_calls_regex = re.compile(interesting_calls_prg, re.IGNORECASE)

def interesting_function(name):
    return re.match(interesting_calls_regex, name) is not None

def filter_and_write_to_temp(obj, f, matcher):
    filtered = []

    for e in obj:
        if 'function' not in e:
            continue
        name = e['function']['name']
        if matcher(name):
            print(name)
            filtered.append(e)

    filtered_and_sorted = sorted(filtered, key=lambda entry: entry['function']['name'])
    json.dump(filtered_and_sorted, f, indent=1)
try:
    filter_and_write_to_temp(nvidia_json, nvidia_out, interesting_function)
    filter_and_write_to_temp(ffmpeg_json, ffmpeg_out, interesting_function)
finally:
    nvidia_out.close()
    nvidia_file.close()
    ffmpeg_out.close()
    ffmpeg_file.close()
