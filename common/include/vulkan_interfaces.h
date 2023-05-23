/*
* Copyright 2020 NVIDIA Corporation.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef DE_BUILD_VIDEO
#ifdef VK_API_USE_DRIVER_REPO
// If using the local driver repo with Vulkan APIs
#include "vulkan/vulkannv.h"
#else
// Using the Vulkan APIs from Vulkan SDK
#ifndef VK_ENABLE_BETA_EXTENSIONS
#define VK_ENABLE_BETA_EXTENSIONS 1
#endif
#include "vulkan/vulkan.h"
#endif

#else

#include "vkDefs.hpp"
using namespace vk;

#endif // !defined(_VKDEFS_H)
