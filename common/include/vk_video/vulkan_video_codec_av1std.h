#ifndef VULKAN_VIDEO_CODEC_AV1STD_H_
#define VULKAN_VIDEO_CODEC_AV1STD_H_ 1

/*
** Copyright 2015-2023 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
extern "C" {
#endif



// vulkan_video_codec_av1std is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codec_av1std 1
#include "vulkan_video_codecs_common.h"
#define STD_VIDEO_AV1_NUM_REF_FRAMES      8
#define STD_VIDEO_AV1_REFS_PER_FRAME      7
#define STD_VIDEO_AV1_TOTAL_REFS_PER_FRAME 8
#define STD_VIDEO_AV1_MAX_TILE_COLS       64
#define STD_VIDEO_AV1_MAX_TILE_ROWS       64
#define STD_VIDEO_AV1_MAX_SEGMENTS        8
#define STD_VIDEO_AV1_SEG_LVL_MAX         8
#define STD_VIDEO_AV1_PRIMARY_REF_NONE    7
#define STD_VIDEO_AV1_SELECT_INTEGER_MV   2

typedef enum StdVideoAV1Profile {
    STD_VIDEO_AV1_PROFILE_MAIN = 0,
    STD_VIDEO_AV1_PROFILE_HIGH = 1,
    STD_VIDEO_AV1_PROFILE_PROFESSIONAL = 2,
    STD_VIDEO_AV1_PROFILE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_PROFILE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Profile;

typedef enum StdVideoAV1Level {
    STD_VIDEO_AV1_LEVEL_2_0 = 0,
    STD_VIDEO_AV1_LEVEL_2_1 = 1,
    STD_VIDEO_AV1_LEVEL_2_2 = 2,
    STD_VIDEO_AV1_LEVEL_2_3 = 3,
    STD_VIDEO_AV1_LEVEL_3_0 = 4,
    STD_VIDEO_AV1_LEVEL_3_1 = 5,
    STD_VIDEO_AV1_LEVEL_3_2 = 6,
    STD_VIDEO_AV1_LEVEL_3_3 = 7,
    STD_VIDEO_AV1_LEVEL_4_0 = 8,
    STD_VIDEO_AV1_LEVEL_4_1 = 9,
    STD_VIDEO_AV1_LEVEL_4_2 = 10,
    STD_VIDEO_AV1_LEVEL_4_3 = 11,
    STD_VIDEO_AV1_LEVEL_5_0 = 12,
    STD_VIDEO_AV1_LEVEL_5_1 = 13,
    STD_VIDEO_AV1_LEVEL_5_2 = 14,
    STD_VIDEO_AV1_LEVEL_5_3 = 15,
    STD_VIDEO_AV1_LEVEL_6_0 = 16,
    STD_VIDEO_AV1_LEVEL_6_1 = 17,
    STD_VIDEO_AV1_LEVEL_6_2 = 18,
    STD_VIDEO_AV1_LEVEL_6_3 = 19,
    STD_VIDEO_AV1_LEVEL_7_0 = 20,
    STD_VIDEO_AV1_LEVEL_7_1 = 21,
    STD_VIDEO_AV1_LEVEL_7_2 = 22,
    STD_VIDEO_AV1_LEVEL_7_3 = 23,
    STD_VIDEO_AV1_LEVEL_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_LEVEL_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Level;

typedef enum StdVideoAV1FrameType {
    STD_VIDEO_AV1_FRAME_TYPE_KEY = 0,
    STD_VIDEO_AV1_FRAME_TYPE_INTER = 1,
    STD_VIDEO_AV1_FRAME_TYPE_INTRA_ONLY = 2,
    STD_VIDEO_AV1_FRAME_TYPE_SWITCH = 3,
    STD_VIDEO_AV1_FRAME_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_FRAME_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1FrameType;

typedef enum StdVideoAV1InterpolationFilter {
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP = 0,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SMOOTH = 1,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SHARP = 2,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_BILINEAR = 3,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_SWITCHABLE = 4,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1InterpolationFilter;

typedef enum StdVideoAV1TxMode {
    STD_VIDEO_AV1_TX_MODE_ONLY_4X4 = 0,
    STD_VIDEO_AV1_TX_MODE_LARGEST = 1,
    STD_VIDEO_AV1_TX_MODE_SELECT = 2,
    STD_VIDEO_AV1_TX_MODE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TX_MODE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1TxMode;
typedef struct StdVideoAV1ColorConfigFlags {
    uint32_t    mono_chrome : 1;
    uint32_t    color_range : 1;
    uint32_t    separate_uv_delta_q : 1;
    uint32_t    reserved : 29;
} StdVideoAV1ColorConfigFlags;

typedef struct StdVideoAV1ColorConfig {
    StdVideoAV1ColorConfigFlags    flags;
    uint8_t                        BitDepth;
    uint8_t                        subsampling_x;
    uint8_t                        subsampling_y;
    uint8_t                        reserved1;
} StdVideoAV1ColorConfig;

typedef struct StdVideoAV1TimingInfoFlags {
    uint32_t    equal_picture_interval : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TimingInfoFlags;

typedef struct StdVideoAV1TimingInfo {
    StdVideoAV1TimingInfoFlags    flags;
    uint32_t                      num_units_in_display_tick;
    uint32_t                      time_scale;
    uint32_t                      num_ticks_per_picture_minus_1;
} StdVideoAV1TimingInfo;

typedef struct StdVideoAV1LoopFilterFlags {
    uint32_t    loop_filter_delta_enabled : 1;
    uint32_t    loop_filter_delta_update : 1;
    uint32_t    reserved : 30;
} StdVideoAV1LoopFilterFlags;

typedef struct StdVideoAV1LoopFilter {
    StdVideoAV1LoopFilterFlags    flags;
    uint8_t                       loop_filter_level[4];
    uint8_t                       loop_filter_sharpness;
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_AV1_TOTAL_REFS_PER_FRAME];
    int8_t                        loop_filter_mode_deltas[2];
    uint8_t                       reserved1[5];
} StdVideoAV1LoopFilter;

typedef struct StdVideoAV1QuantizationFlags {
    uint32_t    using_qmatrix : 1;
    uint32_t    diff_uv_delta : 1;
    uint32_t    reserved : 30;
} StdVideoAV1QuantizationFlags;

typedef struct StdVideoAV1Quantization {
    StdVideoAV1QuantizationFlags    flags;
    uint8_t                         base_q_idx;
    int8_t                          deltaQYDc;
    int8_t                          deltaQUDc;
    int8_t                          deltaQUAc;
    int8_t                          deltaQVDc;
    int8_t                          deltaQVAc;
    uint8_t                         qm_y;
    uint8_t                         qm_u;
    uint8_t                         qm_v;
    uint8_t                         reserved1[3];
} StdVideoAV1Quantization;

typedef struct StdVideoAV1Segmentation {
    uint8_t    FeatureEnabled[STD_VIDEO_AV1_MAX_SEGMENTS];
    int16_t    FeatureData[STD_VIDEO_AV1_MAX_SEGMENTS][STD_VIDEO_AV1_SEG_LVL_MAX];
} StdVideoAV1Segmentation;

typedef struct StdVideoAV1TileInfoFlags {
    uint32_t    uniform_tile_spacing_flag : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TileInfoFlags;

typedef struct StdVideoAV1TileInfo {
    StdVideoAV1TileInfoFlags    flags;
    uint8_t                     tileCols;
    uint8_t                     tileRows;
    uint16_t                    context_update_tile_id;
    const uint16_t*             MiColStarts;
    const uint16_t*             MiRowStarts;
    const uint16_t*             width_in_sbs_minus_1;
    const uint16_t*             height_in_sbs_minus_1;
    uint8_t                     tile_size_bytes_minus_1;
} StdVideoAV1TileInfo;

typedef struct StdVideoAV1CDEF {
    uint8_t    cdef_damping_minus_3;
    uint8_t    cdef_bits;
    uint8_t    cdef_y_pri_strength[8];
    uint8_t    cdef_y_sec_strength[8];
    uint8_t    cdef_uv_pri_strength[8];
    uint8_t    cdef_uv_sec_strength[8];
} StdVideoAV1CDEF;

typedef struct StdVideoAV1LoopRestoration {
    uint8_t    lr_type[3];
    uint8_t    lr_unit_shift;
    uint8_t    lr_uv_shift;
    uint8_t    reserved1[3];
} StdVideoAV1LoopRestoration;

typedef struct StdVideoAV1GlobalMotion {
    uint8_t    GmType[STD_VIDEO_AV1_NUM_REF_FRAMES];
    int32_t    gm_params[STD_VIDEO_AV1_NUM_REF_FRAMES][6];
} StdVideoAV1GlobalMotion;

typedef struct StdVideoAV1FilmGrainFlags {
    uint32_t    chroma_scaling_from_luma : 1;
    uint32_t    overlap_flag : 1;
    uint32_t    clip_to_restricted_range : 1;
    uint32_t    reserved : 29;
} StdVideoAV1FilmGrainFlags;

typedef struct StdVideoAV1FilmGrain {
    StdVideoAV1FilmGrainFlags    flags;
    uint8_t                      grain_scaling_minus_8;
    uint8_t                      ar_coeff_lag;
    uint8_t                      ar_coeff_shift_minus_6;
    uint8_t                      grain_scale_shift;
    uint16_t                     grain_seed;
    uint8_t                      num_y_points;
    uint8_t                      point_y_value[14];
    uint8_t                      point_y_scaling[14];
    uint8_t                      num_cb_points;
    uint8_t                      point_cb_value[10];
    uint8_t                      point_cb_scaling[10];
    uint8_t                      num_cr_points;
    uint8_t                      point_cr_value[10];
    uint8_t                      point_cr_scaling[10];
    int8_t                       ar_coeffs_y_plus_128[24];
    int8_t                       ar_coeffs_cb_plus_128[25];
    int8_t                       ar_coeffs_cr_plus_128[25];
    uint8_t                      cb_mult;
    uint8_t                      cb_luma_mult;
    uint16_t                     cb_offset;
    uint8_t                      cr_mult;
    uint8_t                      cr_luma_mult;
    uint16_t                     cr_offset;
} StdVideoAV1FilmGrain;

typedef struct StdVideoAV1SequenceHeaderFlags {
    uint32_t    still_picture : 1;
    uint32_t    reduced_still_picture_header : 1;
    uint32_t    use_128x128_superblock : 1;
    uint32_t    enable_filter_intra : 1;
    uint32_t    enable_intra_edge_filter : 1;
    uint32_t    enable_interintra_compound : 1;
    uint32_t    enable_masked_compound : 1;
    uint32_t    enable_warped_motion : 1;
    uint32_t    enable_dual_filter : 1;
    uint32_t    enable_order_hint : 1;
    uint32_t    enable_jnt_comp : 1;
    uint32_t    enable_ref_frame_mvs : 1;
    uint32_t    frame_id_numbers_present_flag : 1;
    uint32_t    enable_superres : 1;
    uint32_t    enable_cdef : 1;
    uint32_t    enable_restoration : 1;
    uint32_t    film_grain_params_present : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    initial_display_delay_present_flag : 1;
    uint32_t    seq_choose_screen_content_tools : 1;
    uint32_t    seq_force_screen_content_tools : 1;
    uint32_t    seq_choose_integer_mv : 1;
    uint32_t    seq_force_integer_mv : 1;
    uint32_t    reserved : 9;
} StdVideoAV1SequenceHeaderFlags;

typedef struct StdVideoAV1SequenceHeader {
    StdVideoAV1SequenceHeaderFlags    flags;
    StdVideoAV1Profile                seq_profile;
    uint8_t                           frame_width_bits_minus_1;
    uint8_t                           frame_height_bits_minus_1;
    uint16_t                          max_frame_width_minus_1;
    uint16_t                          max_frame_height_minus_1;
    uint8_t                           delta_frame_id_length_minus_2;
    uint8_t                           additional_frame_id_length_minus_1;
    uint8_t                           order_hint_bits_minus_1;
    uint8_t                           seq_force_integer_mv;
    uint8_t                           reserved1[6];
    StdVideoAV1ColorConfig            color_config;
    StdVideoAV1TimingInfo             timing_info;
} StdVideoAV1SequenceHeader;

typedef struct StdVideoAV1FrameHeaderFlags {
    uint32_t    error_resilient_mode : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_frame_size_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    frame_size_override_flag : 1;
    uint32_t    buffer_removal_time_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    frame_refs_short_signaling : 1;
    uint32_t    allow_high_precision_mv : 1;
    uint32_t    is_motion_mode_switchable : 1;
    uint32_t    use_ref_frame_mvs : 1;
    uint32_t    disable_frame_end_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_set : 1;
    uint32_t    reference_select : 1;
    uint32_t    skip_mode_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_data : 1;
    uint32_t    UsesLr : 1;
    uint32_t    usesChromaLr : 1;
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoAV1FrameHeaderFlags;

typedef struct StdVideoAV1FrameHeader {
    StdVideoAV1FrameHeaderFlags       flags;
    StdVideoAV1FrameType              frame_type;
    uint32_t                          frame_presentation_time;
    uint32_t                          display_frame_id;
    uint32_t                          current_frame_id;
    uint8_t                           frame_to_show_map_idx;
    uint8_t                           order_hint;
    uint8_t                           primary_ref_frame;
    uint8_t                           refresh_frame_flags;
    uint8_t                           ref_order_hint[STD_VIDEO_AV1_NUM_REF_FRAMES];
    uint16_t                          frame_width_minus_1;
    uint16_t                          frame_height_minus_1;
    uint16_t                          render_width_minus_1;
    uint16_t                          render_height_minus_1;
    StdVideoAV1InterpolationFilter    interpolation_filter;
    StdVideoAV1TxMode                 TxMode;
    uint8_t                           coded_denom;
    uint8_t                           delta_q_res;
    uint8_t                           delta_lf_res;
    uint8_t                           reserved1[5];
    uint8_t                           SkipModeFrame[2];
    int8_t                            ref_frame_idx[STD_VIDEO_AV1_REFS_PER_FRAME];
    uint8_t                           delta_frame_id_minus_1[STD_VIDEO_AV1_REFS_PER_FRAME];
    StdVideoAV1LoopFilter             loop_filter;
    StdVideoAV1Quantization           quantization;
    const StdVideoAV1Segmentation*    pSegmentation;
    StdVideoAV1TileInfo               tile_info;
    const StdVideoAV1CDEF*            pCDEF;
    StdVideoAV1LoopRestoration        lr;
    StdVideoAV1GlobalMotion           global_motion;
    const StdVideoAV1FilmGrain*       pFilmGrain;
} StdVideoAV1FrameHeader;


#ifdef __cplusplus
}
#endif

#endif
