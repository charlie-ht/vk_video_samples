#!/usr/bin/env python3

import json
import re
import sys
from typing import Dict, List

infile = open(sys.argv[1], 'r')
injson = json.load(infile)

resource_names = [
   #"vkCreateBuffer",
    "vkCreateImage",
    "vkCreateImageView",
]
names = [
    # "vkAllocateCommandBuffers",
    # "vkAllocateMemory",
    # "vkBeginCommandBuffer",
    # "vkBindBufferMemory",
    # "vkBindImageMemory",
    "vkBindVideoSessionMemoryKHR",
    "vkCmdBeginVideoCodingKHR",
    "vkCmdControlVideoCodingKHR",
    "vkCmdDecodeVideoKHR",
    "vkCmdEndVideoCodingKHR",
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
    "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    # "vkGetVideoSessionMemoryRequirementsKHR",
    # "vkMapMemory",
    # "vkQueueSubmit",
    # "vkQueueWaitIdle",
    # "vkResetFences",
    # "vkUnmapMemory",
    # "vkWaitForFences",
]
video_operation_prg = r'|'.join(names)
video_operation_regex = re.compile(video_operation_prg, re.IGNORECASE)

resource_calls_prg = r'|'.join(resource_names)
resource_calls_regex = re.compile(resource_calls_prg, re.IGNORECASE)

def video_operation(name):
    return re.match(video_operation_regex, name) is not None

def resource_function(name):
    return re.match(resource_calls_regex, name) is not None

def filter_resources(obj, matcher):
    filtered = []

    for e in obj:
        if 'function' not in e:
            continue
        name = e['function']['name']
        if matcher(name):
            filtered.append(e)
    
    return filtered


image_create_flags = {
    0x00000001: "VK_IMAGE_CREATE_SPARSE_BINDING_BIT",
    0x00000002: "VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT",
    0x00000004: "VK_IMAGE_CREATE_SPARSE_ALIASED_BIT",
    0x00000008: "VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT",
    0x00000010: "VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT",
    0x00000400: "VK_IMAGE_CREATE_ALIAS_BIT",
    0x00000040: "VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT",
    0x00000020: "VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT",
    0x00000080: "VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT",
    0x00000100: "VK_IMAGE_CREATE_EXTENDED_USAGE_BIT",
    0x00000800: "VK_IMAGE_CREATE_PROTECTED_BIT",
    0x00000200: "VK_IMAGE_CREATE_DISJOINT_BIT",
    0x00002000: "VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV",
    0x00001000: "VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT",
    0x00004000: "VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT",
    0x00010000: "VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT"
}

# create another map like the one above, but the for enumeration values within the VkImageUsageFlagBits enum
image_create_usage = {
    0x00000001: "VK_IMAGE_USAGE_TRANSFER_SRC_BIT",
    0x00000002: "VK_IMAGE_USAGE_TRANSFER_DST_BIT",
    0x00000004: "VK_IMAGE_USAGE_SAMPLED_BIT",
    0x00000008: "VK_IMAGE_USAGE_STORAGE_BIT",
    0x00000010: "VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT",
    0x00000020: "VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT",
    0x00000040: "VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT",
    0x00000080: "VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT",
    0x00000400: "VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR",
    0x00000800: "VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR",
    0x00001000: "VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR",
}

# create a mapping with the contents of VkVideoCodecOperationFlagBitsKHR
video_codec_operation = {
    0x00000001: "VK_VIDEO_CODEC_OPERATION_INVALID_BIT_KHR",
    0x00000002: "VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR",
    0x00000004: "VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR",
    0x01000000: "VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_MESA"
}

image_view_aspect = {
    # create a mapping of all the enumerants from VkImageAspectFlagBits, taking their enumerant value and mapping it to the enumerant string
    0x00000001: "VK_IMAGE_ASPECT_COLOR_BIT",
    0x00000002: "VK_IMAGE_ASPECT_DEPTH_BIT",
    0x00000010: "VK_IMAGE_ASPECT_PLANE_0_BIT",
    0x00000020: "VK_IMAGE_ASPECT_PLANE_1_BIT",
    0x00000040: "VK_IMAGE_ASPECT_PLANE_2_BIT"
}

decode_usage_flags = {
    0x00000000: "VK_VIDEO_DECODE_USAGE_DEFAULT_KHR",
    0x00000001: "VK_VIDEO_DECODE_USAGE_TRANSCODING_BIT_KHR",
    0x00000002: "VK_VIDEO_DECODE_USAGE_OFFLINE_BIT_KHR",
    0x00000004: "VK_VIDEO_DECODE_USAGE_STREAMING_BIT_KHR",
}

from dataclasses import dataclass

IMAGE_RESOURCE_TYPE = 1
IMAGEVIEW_RESOURCE_TYPE = 2

@dataclass
class Profile:
    video_codec_operation: str = None
    chroma_subsampling: str = None
    chroma_bitdepth: str = None
    luma_bitdepth: str = None

    video_usage_hints: str = None
    profile_idc: str = None

    def as_str(self, level=1) -> str:
        assert level > 0
        inner_indent = '\t' * (level - 1)
        s = f"{inner_indent}Profile:\n"
        if self.video_codec_operation:
            s += f"{inner_indent}\tVideo codec operation: {self.video_codec_operation}\n"
        if self.chroma_subsampling:
            s += f"{inner_indent}\tChroma subsampling: {self.chroma_subsampling}\n"
        if self.chroma_bitdepth:
            s += f"{inner_indent}\tChroma bitdepth: {self.chroma_bitdepth}\n"
        if self.luma_bitdepth:
            s += f"{inner_indent}\tLuma bitdepth: {self.luma_bitdepth}\n"
        if self.video_usage_hints:
            s += f"{inner_indent}\tVideo usage hints: {self.video_usage_hints}\n"
        if self.profile_idc:
            s += f"{inner_indent}\tProfile IDC: {self.profile_idc}\n"
        return s

@dataclass
class ImageResource:
    type: int
    idx: int
    shorthand: str
    fmt: str
    extent: str
    queue_family_indices: str
    flags: str
    usage: str
    tiling: str

    profiles: List[Profile]

    def as_str(self, level=1) -> str:
        inner_indent = '\t' * level
        s = '\t' * (level -1) + f"""ImageResource({self.idx})    {self.shorthand}
{inner_indent}Format: {self.fmt}
{inner_indent}Extent: {self.extent}
{inner_indent}QF indices: {self.queue_family_indices}
{inner_indent}Flags: {self.flags}
{inner_indent}Usage: {self.usage}
{inner_indent}Tiling: {self.tiling}
"""
        s += "\tProfiles:\n"
        for p in self.profiles:
            s += f"{p.as_str(level=level + 2)}\n"
        return s

    def __hash__(self) -> int:
        return self.idx

@dataclass
class ImageViewResource:
    type: int
    view_idx: int
    image_idx: int
    aspect_mask: str
    base_array_layer: int
    base_mip_level: int
    layer_count: int
    level_count: int

    def as_str(self, level = 1) -> str:
        inner_indent = '\t' * level
        return '\t' * (level -1) + f"""ImageView {self.view_idx} of image {self.image_idx}
Aspect: {self.aspect_mask}
Base array layer: {self.base_array_layer}
Base mip level: {self.base_mip_level}
Layer count: {self.layer_count}
Level count: {self.level_count}
Image:\n{resources[self.image_idx].as_str(level=level+1)}
"""

@dataclass
class DpbSlot:
    image_view_idx: int
    slot_idx: int
    coded_extent: str
    shorthand: str
    objs: List[any]
    metadata: Dict[str, any]

    def as_str(self, level = 1) -> str:
        assert level > 0
        inner_indent = '\t' * (level - 1)
        image_view = resources[image_view_idx]
        return f"""{inner_indent}DpbSlot View={self.image_view_idx} {self.coded_extent} {self.shorthand}
ImageView: {image_view.as_str(level + 1)}
MetaData: {self.metadata}
"""



def flags_as_str(flags, map):
    s = []
    if flags == 0:
        return '(clear)'
    for k, v in map.items():
        if flags & k:
            s.append(v)
        flags &= ~k
    if flags:
        s.append(f"UNKNOWN FLAGS {flags}")
    return '|'.join(s)

resources = {}


def process_create_image(args):
    create_info = args['pCreateInfo']
    fmt = create_info['format']
    flags = flags_as_str(int(create_info['flags'], 0), image_create_flags)
    usage = flags_as_str(int(create_info['usage'], 0), image_create_usage)
    extent = create_info['extent']
    queue_family_indices = create_info['pQueueFamilyIndices']
    image_idx = args['pImage']
    tiling = create_info['tiling']
    
    #print(json.dumps(args, indent=4))

    pnext = create_info['pNext']
    profiles = []

    while pnext is not None:
        if pnext['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR':
            profile_list = pnext['pProfiles']
            for i, profile in enumerate(profile_list):
                assert(profile['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR')
                video_codec_operation = profile['videoCodecOperation']
                p = Profile()
                p.video_codec_operation = video_codec_operation
                profile_next = profile['pNext']
                while profile_next is not None:
                    if profile_next['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PROFILE_INFO_MESA':
                        p.profile_idc = profile_next['stdProfileIdc']
        
                    elif profile_next['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_DECODE_USAGE_INFO_KHR':
                        p.video_usage_hints = flags_as_str(int(profile_next['videoUsageHints'], 0), decode_usage_flags)
                    
                    else:
                        print(f"Ignoring (in profile pNext chain) structure {profile_next['sType']}")
                    
                    profile_next = profile_next['pNext']

            
            profiles.append(p)
        
        print(f"Ignoring {pnext['sType']}")
        pnext = pnext['pNext']

    shorthand = ''
    if 'DECODE_DST' in usage and 'DECODE_DPB' in usage:
        shorthand += ' Both'
    elif 'DECODE_DST' in usage:
        shorthand += ' Destination-only'
    elif 'DECODE_DPB' in usage:
        shorthand += ' Dpb-only'
    
    r = ImageResource(IMAGE_RESOURCE_TYPE, image_idx, shorthand, fmt, extent, queue_family_indices, flags, usage, tiling, profiles)
    resources[image_idx] = r
    
    #print(f";;;;; {image_idx} {shorthand} {profileIdc} {fmt}\n\t{extent}\n\t{queue_family_indices}\n\t{flags}\n\t{usage}\n\t{tiling}\n\t{videoCodecOperation}")


def process_create_image_view(args):
    create_info = args['pCreateInfo']
    assert create_info['sType'] == 'VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO'
    image_idx = create_info['image']
    assert image_idx in resources
    subresource_range = create_info['subresourceRange']
    aspect_mask = flags_as_str(int(subresource_range['aspectMask'], 0), image_view_aspect)
    base_array_layer = subresource_range['baseArrayLayer']
    base_mip_level  = subresource_range['baseMipLevel']
    layer_count = subresource_range['layerCount']
    level_count = subresource_range['levelCount']
    view_idx = args['pView']
    r = ImageViewResource(IMAGEVIEW_RESOURCE_TYPE, view_idx, image_idx, aspect_mask, base_array_layer, base_mip_level, layer_count, level_count)
    resources[view_idx] = r

resource_objs_json = filter_resources(injson, resource_function)
# pretty print resource_objs_json to stdout
#print(json.dumps(resource_objs_json, indent=4, sort_keys=True))
# for each of the objects, print the name and args of the object
for e in resource_objs_json:
    name = e['function']['name']
    args = e['function']['args']
    #print(f"{name}({args})")
    if name == 'vkCreateImage':
        process_create_image(args)
    elif name == 'vkCreateImageView':
        process_create_image_view(args)

for obj in resources.values():
    print(obj.as_str())
        # print(f";;;;;; ImageView {obj.view_idx} {obj.aspect_mask} base_arr={obj.base_array_layer} base_mip={obj.base_mip_level} nlayer={obj.layer_count} nlevel={obj.level_count}")
        # image_obj = resources[obj.image_idx]
        # print(f"\t -> Image {image_obj.idx} {image_obj.shorthand} {image_obj.fmt}\n\t\t{image_obj.extent}\n\t\t{image_obj.queue_family_indices}\n\t\t{image_obj.flags}\n\t\t{image_obj.usage}\n\t\t{image_obj.tiling}")
        # print(f"\t\tProfiles:")
        # for p in image_obj.profiles:
        #     print(f"\t\t\t{p.video_codec_operation} {p.profile_idc} usage_flags={p.video_usage_hints}")

video_operations = filter_resources(injson, video_operation)
loop_counter = 0


image_in_session = set()
for vo in sorted(video_operations, key=lambda vo: vo['index']):
    #print(json.dumps(vo, indent=4, sort_keys=True))

    if vo['function']['name'] == 'vkCmdBeginVideoCodingKHR':
        args = vo['function']['args']
        begin_info = args['pBeginInfo']
        reference_slots = begin_info['pReferenceSlots']
        num_slots = begin_info['referenceSlotCount']
        if num_slots == 0:
            continue
        slots = []
        shorthand = ''
        #print(json.dumps(args, indent=4))

        loop_counter += 1
        print("Begin Coding session", loop_counter)
                
        for slot_scoper in reference_slots:
            slot_idx = slot_scoper['slotIndex']
            picture_resource = slot_scoper['pPictureResource']
            coded_extent = picture_resource['codedExtent']
            coded_extent_str = f"{coded_extent['width']}x{coded_extent['height']}"
            if slot_idx == -1:
                shorthand += '*'
            image_view_idx = picture_resource['imageViewBinding']
            pnext = slot_scoper['pNext']
            objs = []
            md = {}
            while pnext is not None:
                if pnext['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_DPB_SLOT_INFO_MESA':
                    objs.append(pnext)
                    md['frame_idx'] = pnext['frame_idx']
                    md['ref_order_hints'] = pnext['ref_order_hints']
                    assert pnext['pNext'] is None
                    
                elif pnext['sType'] == 'VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR':
                    objs.append(pnext)
                    ref_info = pnext['pStdReferenceInfo']
                    md['ref_info'] = ref_info
                    assert pnext['pNext'] is None
                else:
                    print(f"Ignoring {pnext['sType']}")
                    assert False and f"Ignoring {pnext['sType']}"
                pnext = pnext['pNext']
            slots.append(DpbSlot(image_view_idx, slot_idx, coded_extent_str, shorthand, objs, md))
    
        import pprint
        #pprint.pp(slots)

        num_images_in_frame = set()
        print(f"Num reference slots: {len(slots)}")
        for i, slot in enumerate(slots):
            image_view = resources[slot.image_view_idx]
            image = resources[image_view.image_idx]
            num_images_in_frame.add(image)
            image_in_session.add(image)
            print(f"""Slot {i}: {image.idx : >3} | {slot.slot_idx : >2} | {slot.coded_extent} | {slot.metadata}""")
        print(f"unique imgs in frame: {len(num_images_in_frame)}")

print(f"unique imgs: {len(image_in_session)}")

