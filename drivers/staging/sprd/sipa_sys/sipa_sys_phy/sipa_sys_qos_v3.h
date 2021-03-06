#ifndef __SIPA_SYS_QOS_V3_H__
#define __SIPA_SYS_QOS_V3_H__

struct qos_reg {
	const char *reg_name;
	u32 base_addr;
	u32 mask_value;
	u32 set_value;
};

static struct qos_reg nic400_ipa_main_mtx_m2_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x25303100, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x25303104, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x25303108, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x2530310C, 0x3f3fffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x25303140, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x25303144, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x25303148, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x2530314C, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x25303150, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x25303160, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x25303164, 0x3fff3fff, 0x09990999},
	{"REGU_URG_CNT_CFG", 0x25303168, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_ipa_main_mtx_m3_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x25303180, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x25303184, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x25303188, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x2530318C, 0x3f3fffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x253031C0, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x253031C4, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x253031C8, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x253031CC, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x253031D0, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x253031E0, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x253031E4, 0x3fff3fff, 0x09990999},
	{"REGU_URG_CNT_CFG", 0x253031E8, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_ipa_main_mtx_m4_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x25303200, 0x00000001, 0x00000001},
	{"REGU_OT_CTRL_AW_CFG", 0x25303204, 0xffffffff, 0x01606f6f},
	{"REGU_OT_CTRL_AR_CFG", 0x25303208, 0x3f3f3f3f, 0x03030303},
	{"REGU_OT_CTRL_Ax_CFG", 0x2530320C, 0x3f3fffff, 0x14140504},
	{"REGU_LAT_EN", 0x25303210, 0x00000003, 0x00000000},
	{"REGU_LAT_W_CFG", 0x25303214, 0xffffffff, 0x00000000},
	{"REGU_LAT_R_CFG", 0x25303218, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x25303240, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x25303244, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x25303248, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x2530324C, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x25303250, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x25303260, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x25303264, 0x3fff3fff, 0x09990999},
	{"REGU_URG_CNT_CFG", 0x25303268, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_ipa_main_mtx_m5_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x25303280, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x25303284, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x25303288, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x2530328C, 0x3f3fffff, 0x00000000},
	{"REGU_LAT_EN", 0x25303290, 0x00000003, 0x00000000},
	{"REGU_LAT_W_CFG", 0x25303294, 0xffffffff, 0x00000000},
	{"REGU_LAT_R_CFG", 0x25303298, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x253032C0, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x253032C4, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x253032C8, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x253032CC, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x253032D0, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x253032E0, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x253032E4, 0x3fff3fff, 0x09990999},
	{"REGU_URG_CNT_CFG", 0x253032E8, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_ipa_main_mtx_m6_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x25303300, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x25303304, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x25303308, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x2530330C, 0x3f3fffff, 0x00000000},
	{"REGU_LAT_EN", 0x25303310, 0x00000003, 0x00000000},
	{"REGU_LAT_W_CFG", 0x25303314, 0xffffffff, 0x00000000},
	{"REGU_LAT_R_CFG", 0x25303318, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x25303340, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x25303344, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x25303348, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x2530334C, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x25303350, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x25303360, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x25303364, 0x3fff3fff, 0x09990999},
	{"REGU_URG_CNT_CFG", 0x25303368, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_dpu_lite_mtx_m0_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x31980000, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x31980004, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x31980008, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x3198000C, 0x3f3fffff, 0x00000000},
	{"REGU_LAT_EN", 0x31980010, 0x00000003, 0x00000000},
	{"REGU_LAT_W_CFG", 0x31980014, 0xffffffff, 0x00000000},
	{"REGU_LAT_R_CFG", 0x31980018, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x31980040, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x31980044, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x31980048, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x3198004C, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x31980050, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x31980060, 0x80000003, 0x00000003},
	{"REGU_AXQOS_GEN_CFG", 0x31980064, 0x3fff3fff, 0x06660dda},
	{"REGU_URG_CNT_CFG", 0x31980068, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg nic400_dpu_lite_mtx_m1_qos_list[] = {
	{"REGU_OT_CTRL_EN", 0x31980080, 0x00000001, 0x00000000},
	{"REGU_OT_CTRL_AW_CFG", 0x31980084, 0xffffffff, 0x00000000},
	{"REGU_OT_CTRL_AR_CFG", 0x31980088, 0x3f3f3f3f, 0x00000000},
	{"REGU_OT_CTRL_Ax_CFG", 0x3198008C, 0x3f3fffff, 0x00000000},
	{"REGU_LAT_EN", 0x31980090, 0x00000003, 0x00000000},
	{"REGU_LAT_W_CFG", 0x31980094, 0xffffffff, 0x00000000},
	{"REGU_LAT_R_CFG", 0x31980098, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_EN", 0x319800C0, 0x00000003, 0x00000000},
	{"REGU_BW_NRT_W_CFG_0", 0x319800C4, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_W_CFG_1", 0x319800C8, 0x073fffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_0", 0x319800CC, 0xffffffff, 0x00000000},
	{"REGU_BW_NRT_R_CFG_1", 0x319800D0, 0x073fffff, 0x00000000},
	{"REGU_AXQOS_GEN_EN", 0x319800E0, 0x80000003, 0x00000000},
	{"REGU_AXQOS_GEN_CFG", 0x319800E4, 0x3fff3fff, 0x06660dda},
	{"REGU_URG_CNT_CFG", 0x319800E8, 0x00000701, 0x00000001},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg dispc1_glb_apb_rf_qos_list[] = {
	{"DISPC1_M0_LPC", 0x31800030, 0x00010000, 0x00000000},
	{"DISPC1_M0_LPC", 0x31800030, 0x00010000, 0x00010000},
	{"DISPC1_M1_LPC", 0x31800034, 0x00010000, 0x00000000},
	{"DISPC1_M1_LPC", 0x31800034, 0x00010000, 0x00010000},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

static struct qos_reg ipa_apb_rf_qos_list[] = {
	{"M0_LPC", 0x25000010, 0x00010000, 0x00000000},
	{"M0_LPC", 0x25000010, 0x00010000, 0x00010000},
	{"M1_LPC", 0x25000014, 0x00010000, 0x00000000},
	{"M1_LPC", 0x25000014, 0x00010000, 0x00010000},
	{"M2_LPC", 0x25000018, 0x00010000, 0x00000000},
	{"M2_LPC", 0x25000018, 0x00010000, 0x00010000},
	{"M3_LPC", 0x2500001C, 0x00010000, 0x00000000},
	{"M3_LPC", 0x2500001C, 0x00010000, 0x00010000},
	{"M4_LPC", 0x25000020, 0x00010000, 0x00000000},
	{"M4_LPC", 0x25000020, 0x00010000, 0x00010000},
	{"M5_LPC", 0x25000024, 0x00010000, 0x00000000},
	{"M5_LPC", 0x25000024, 0x00010000, 0x00010000},
	{"M6_LPC", 0x25000028, 0x00010000, 0x00000000},
	{"M6_LPC", 0x25000028, 0x00010000, 0x00010000},
	{"M7_LPC", 0x2500002C, 0x00010000, 0x00000000},
	{"M7_LPC", 0x2500002C, 0x00010000, 0x00010000},
	{"M8_LPC", 0x25000030, 0x00010000, 0x00000000},
	{"M8_LPC", 0x25000030, 0x00010000, 0x00010000},
	{"end", 0x00000000, 0x00000000, 0x00000000}
};

#endif
