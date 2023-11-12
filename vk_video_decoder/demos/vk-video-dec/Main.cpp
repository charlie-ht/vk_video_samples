/*
 * Copyright (C) 2016 Google, Inc.
 * Copyright 2020 NVIDIA Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include "VkCodecUtils/VulkanDeviceContext.h"
#include "VkCodecUtils/FrameProcessorFactory.h"
#include "VkCodecUtils/ProgramConfig.h"
#include "VkCodecUtils/VulkanVideoProcessor.h"
#include "VkShell/Shell.h"

int main(int argc, const char **argv) {

    ProgramConfig programConfig(argv[0]);
    programConfig.ParseArgs(argc, argv);

    static const char* const requiredInstanceLayerExtensions[] = {
        "VK_LAYER_KHRONOS_validation",
        nullptr
    };

    static const char* const requiredWsiInstanceExtensions[] = {
        // Required generic WSI extensions
        VK_KHR_SURFACE_EXTENSION_NAME,
        nullptr
    };

    static const char* const requiredDeviceExtension[] = {
#if defined(__linux) || defined(__linux__) || defined(linux)
        VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,
        VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME,
#endif
        VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,
        VK_KHR_VIDEO_QUEUE_EXTENSION_NAME,
        VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME,
        nullptr
    };

    static const char* const requiredWsiDeviceExtension[] = {
        // Add the WSI required device extensions
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#if !defined(VK_USE_PLATFORM_WIN32_KHR)
        // VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME,
#endif
        nullptr
    };

    static const char* const optinalDeviceExtension[] = {
        VK_EXT_YCBCR_2PLANE_444_FORMATS_EXTENSION_NAME,
        VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME,
        VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
        VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,
        nullptr
    };

    std::vector<const char *> reqInstanceExtensions;
    std::vector<const char *> reqDeviceExtensions;

    if (programConfig.validate)
        reqInstanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    /********** Start WSI instance extensions support *******************************************/
    if (!programConfig.noPresent) {
        const std::vector<VkExtensionProperties>& wsiRequiredInstanceInstanceExtensions =
                Shell::GetRequiredInstanceExtensions(programConfig.directMode);

        for (size_t e = 0; e < wsiRequiredInstanceInstanceExtensions.size(); e++) {
            reqInstanceExtensions.push_back(wsiRequiredInstanceInstanceExtensions[e].extensionName);
        }

        for (uint32_t i = 0; requiredWsiInstanceExtensions[0]; i++) {
            const char* name = requiredWsiInstanceExtensions[i];
            if (name == nullptr) {
                break;
            }
            reqInstanceExtensions.push_back(name);
        }
        // terminate the reqInstanceExtensions list with nullptr
        reqInstanceExtensions.push_back(nullptr);

        // Add the WSI required device extensions
        for (uint32_t i = 0; requiredWsiDeviceExtension[0]; i++) {
            const char* name = requiredWsiDeviceExtension[i];
            if (name == nullptr) {
                break;
            }
            reqDeviceExtensions.push_back(name);
        }
    }
    /********** End WSI instance extensions support *******************************************/

    // Add the Vulkan video required device extensions
    for (uint32_t i = 0; requiredDeviceExtension[0]; i++) {
        const char* name = requiredDeviceExtension[i];
        if (name == nullptr) {
            break;
        }
        reqDeviceExtensions.push_back(name);
    }
    // terminate the reqDeviceExtensions list with nullptr
    reqDeviceExtensions.push_back(nullptr);

    VulkanDeviceContext vkDevCtxt(programConfig.deviceId,
            programConfig.validate ? requiredInstanceLayerExtensions : nullptr,
            reqInstanceExtensions.data(),
            reqDeviceExtensions.data(),
            optinalDeviceExtension);

    VkResult result = vkDevCtxt.InitVulkanDevice(programConfig.name.c_str(),
                                                 programConfig.verbose);
    if (result != VK_SUCCESS) {
        printf("Could not initialize the Vulkan device!\n");
        return -1;
    }

    result = vkDevCtxt.InitDebugReport(programConfig.validate,
                                       programConfig.validateVerbose);
    if (result != VK_SUCCESS) {
        return -1;
    }

    VkSharedBaseObj<VulkanVideoProcessor> vulkanVideoProcessor;
    result = VulkanVideoProcessor::Create(&vkDevCtxt, vulkanVideoProcessor);
    if (result != VK_SUCCESS) {
        return -1;
    }

    VkSharedBaseObj<FrameProcessor> frameProcessor;
    result = CreateFrameProcessor(programConfig, &vkDevCtxt, vulkanVideoProcessor, frameProcessor);
    if (result != VK_SUCCESS) {
        return -1;
    }

    const bool supportsDisplay = true;
    const int32_t numDecodeQueues = ((programConfig.queueId != 0) ||
                                     (programConfig.enableHwLoadBalancing != 0)) ?
					 -1 : // all available HW decoders
					  1;  // only one HW decoder instance

    VkQueueFlags requestVideoDecodeQueueMask = VK_QUEUE_VIDEO_DECODE_BIT_KHR |
                                               VK_QUEUE_TRANSFER_BIT;

    VkQueueFlags requestVideoEncodeQueueMask = 0;
#ifdef DECODER_ADD_ENCODER_QUEUE
    requestVideoEncodeQueueMask |= VK_QUEUE_VIDEO_ENCODE_BIT_KHR |
                                   VK_QUEUE_TRANSFER_BIT;
#endif // DECODER_ADD_ENCODER_QUEUE

    if (programConfig.selectVideoWithComputeQueue) {
        requestVideoDecodeQueueMask |= VK_QUEUE_COMPUTE_BIT;
#ifdef DECODER_ADD_ENCODER_QUEUE
        requestVideoEncodeQueueMask |= VK_QUEUE_COMPUTE_BIT;
#endif // DECODER_ADD_ENCODER_QUEUE
    }

    if (supportsDisplay && !programConfig.noPresent) {

        VkSharedBaseObj<Shell> displayShell;
        result = Shell::Create(&vkDevCtxt, frameProcessor, programConfig.directMode, displayShell);
        if (result != VK_SUCCESS) {
            assert(!"Can't allocate display shell! Out of memory!");
            return -1;
        }

        result = vkDevCtxt.InitPhysicalDevice((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT | VK_QUEUE_COMPUTE_BIT |
                                               VK_QUEUE_VIDEO_DECODE_BIT_KHR | VK_QUEUE_VIDEO_ENCODE_BIT_KHR),
                                               displayShell,
                                               requestVideoDecodeQueueMask,
                                               (VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR |
                                                VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR),
                                               requestVideoEncodeQueueMask,
                                               (VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT |
                                                VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_EXT));
        if (result != VK_SUCCESS) {

            assert(!"Can't initialize the Vulkan physical device!");
            return -1;
        }
        assert(displayShell->PhysDeviceCanPresent(vkDevCtxt.getPhysicalDevice(),
                                                   vkDevCtxt.GetPresentQueueFamilyIdx()));

        vkDevCtxt.CreateVulkanDevice(numDecodeQueues,
                                     0,    // num encode queues
                                     true, // createGraphicsQueue
                                     true, // createDisplayQueue
                                     true // createComputeQueue
                                     );
        vulkanVideoProcessor->Initialize(&vkDevCtxt, programConfig);


        displayShell->RunLoop();

    } else {

        result = vkDevCtxt.InitPhysicalDevice((VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT |
                                               VK_QUEUE_VIDEO_DECODE_BIT_KHR),
                                               nullptr,
                                               requestVideoDecodeQueueMask);
        if (result != VK_SUCCESS) {

            assert(!"Can't initialize the Vulkan physical device!");
            return -1;
        }

        result = vkDevCtxt.CreateVulkanDevice(numDecodeQueues,
                                              0,     // num encode queues
                                              false, // createGraphicsQueue
                                              false, // createDisplayQueue
                                              true   // createComputeQueue
                                              );
        if (result != VK_SUCCESS) {

            assert(!"Failed to create Vulkan device!");
            return -1;
        }

        vulkanVideoProcessor->Initialize(&vkDevCtxt, programConfig);

        const int numberOfFrames = programConfig.decoderQueueSize;
        int ret = frameProcessor->CreateFrameData(numberOfFrames);
        assert(ret == numberOfFrames);
        if (ret != numberOfFrames) {
            return -1;
        }
        bool continueLoop = true;
        do {
            continueLoop = frameProcessor->OnFrame(0);
        } while (continueLoop);
        frameProcessor->DestroyFrameData();
    }

    return 0;
}
