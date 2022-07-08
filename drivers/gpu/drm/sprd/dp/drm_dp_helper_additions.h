// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2016 Synopsys, Inc.
 * Copyright (C) 2020 Unisoc Inc.
 */

#include <linux/version.h>

#ifndef __DRM_DP_HELPER_ADDITIONS_H__
#define __DRM_DP_HELPER_ADDITIONS_H__

/*
 * The following aren't yet defined in kernel headers
 */

#define DP_LINK_BW_8_1				0x1e
#define DP_TRAINING_PATTERN_4			7
#define DP_TPS4_SUPPORTED			BIT(7)
#define DP_TEST_H_TOTAL_MSB                     0x222
#define DP_TEST_H_TOTAL_LSB			0x223
#define DP_TEST_V_TOTAL_MSB                     0x224
#define DP_TEST_V_TOTAL_LSB			0x225
#define DP_TEST_H_START_MSB			0x226
#define DP_TEST_H_START_LSB			0x227
#define DP_TEST_V_START_MSB			0x228
#define DP_TEST_V_START_LSB			0x229
#define DP_TEST_H_SYNC_WIDTH_MSB		0x22A
#define DP_TEST_H_SYNC_WIDTH_LSB		0x22B
#define DP_TEST_V_SYNC_WIDTH_MSB		0x22C
#define DP_TEST_V_SYNC_WIDTH_LSB		0x22D
#define DP_TEST_H_WIDTH_MSB			0x22E
#define DP_TEST_H_WIDTH_LSB			0x22F
#define DP_TEST_V_WIDTH_MSB			0x230
#define DP_TEST_V_WIDTH_LSB			0x231
#define DP_TEST_PHY_PATTERN			0x248
#define DP_TEST_PATTERN_NONE			0x0
#define DP_TEST_PATTERN_COLOR_RAMPS		0x1
#define DP_TEST_PATTERN_BW_VERITCAL_LINES	0x2
#define DP_TEST_PATTERN_COLOR_SQUARE		0x3

#define DP_TEST_80BIT_CUSTOM_PATTERN_0		0x250
#define DP_TEST_80BIT_CUSTOM_PATTERN_1		0x251
#define DP_TEST_80BIT_CUSTOM_PATTERN_2		0x252
#define DP_TEST_80BIT_CUSTOM_PATTERN_3		0x253
#define DP_TEST_80BIT_CUSTOM_PATTERN_4		0x254
#define DP_TEST_80BIT_CUSTOM_PATTERN_5		0x255
#define DP_TEST_80BIT_CUSTOM_PATTERN_6		0x256
#define DP_TEST_80BIT_CUSTOM_PATTERN_7		0x257
#define DP_TEST_80BIT_CUSTOM_PATTERN_8		0x258
#define DP_TEST_80BIT_CUSTOM_PATTERN_9		0x259

#define DP_TEST_PHY_PATTERN_SEL_MASK		GENMASK(2, 0)
#define DP_TEST_PHY_PATTERN_NONE		0x0
#define DP_TEST_PHY_PATTERN_D10			0x1
#define DP_TEST_PHY_PATTERN_SEMC		0x2
#define DP_TEST_PHY_PATTERN_PRBS7		0x3
#define DP_TEST_PHY_PATTERN_CUSTOM		0x4
#define DP_TEST_PHY_PATTERN_CP2520_1		0x5
#define DP_TEST_PHY_PATTERN_CP2520_2		0x6
#define DP_TEST_PHY_PATTERN_CP2520_3_TPS4	0x7

#define DP_TEST_MISC				0x232
#define DP_TEST_DYNAMIC_RANGE_SHIFT             3
#define DP_TEST_DYNAMIC_RANGE_MASK		BIT(3)
#define DP_TEST_YCBCR_COEFF_SHIFT		4
#define DP_TEST_YCBCR_COEFF_MASK		BIT(4)
#define DP_TEST_BIT_DEPTH_SHIFT			5

#define DP_TEST_DYNAMIC_RANGE_VESA		0x0
#define DP_TEST_LINK_AUDIO_PATTERN		BIT(5)

#define DP_TEST_COLOR_FORMAT_RGB	        0x0
#define DP_TEST_COLOR_FORMAT_YCBCR422           0x2
#define DP_TEST_COLOR_FORMAT_YCBCR444		0x4
#define DP_TEST_YCBCR_COEFF_ITU601		0x0
#define DP_TEST_YCBCR_COEFF_ITU709		0x1

#define	DP_TEST_AUDIO_MODE			0x271
#define DP_TEST_AUDIO_SAMPLING_RATE_MASK	GENMASK(3, 0)
#define DP_TEST_AUDIO_CH_COUNT_SHIFT		4
#define DP_TEST_AUDIO_CH_COUNT_MASK		GENMASK(7, 4)

#define DP_TEST_AUDIO_SAMPLING_RATE_32		0x0
#define DP_TEST_AUDIO_SAMPLING_RATE_44_1	0x1
#define DP_TEST_AUDIO_SAMPLING_RATE_48		0x2
#define DP_TEST_AUDIO_SAMPLING_RATE_88_2	0x3
#define DP_TEST_AUDIO_SAMPLING_RATE_96		0x4
#define DP_TEST_AUDIO_SAMPLING_RATE_176_4	0x5
#define DP_TEST_AUDIO_SAMPLING_RATE_192		0x6

#define DP_TEST_AUDIO_CHANNEL1			0x0
#define DP_TEST_AUDIO_CHANNEL2			0x1
#define DP_TEST_AUDIO_CHANNEL3			0x2
#define DP_TEST_AUDIO_CHANNEL4			0x3
#define DP_TEST_AUDIO_CHANNEL5			0x4
#define DP_TEST_AUDIO_CHANNEL6			0x5
#define DP_TEST_AUDIO_CHANNEL7			0x6
#define DP_TEST_AUDIO_CHANNEL8			0x7


static inline bool
drm_dp_tps4_supported(const u8 dpcd[DP_RECEIVER_CAP_SIZE])
{
	return dpcd[DP_DPCD_REV] >= 0x14 &&
		dpcd[DP_MAX_DOWNSPREAD] & DP_TPS4_SUPPORTED;
}

#define DP_EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT BIT(7)

#endif
