#ifndef _SC2342_GLB_H_
#define _SC2342_GLB_H_

/* ap cp sync flag */
#define MARLIN_CP_INIT_READY_MAGIC	(0xababbaba)
#define MARLIN_CP_INIT_START_MAGIC	(0x5a5a5a5a)
#define MARLIN_CP_INIT_SUCCESS_MAGIC	(0x13579bdf)
#define MARLIN_CP_INIT_FAILED_MAGIC	(0x88888888)

/* SUB_NAME len not more than 15 bytes */
#define WCN_DUMP_VERSION_SUB_NAME "SIPC_23xx"
/* CP2 iram start and end */
#define WCN_DUMP_CP2_IRAM_START 1
#define WCN_DUMP_CP2_IRAM_END 2
/* AP regs start and end */
#define WCN_DUMP_AP_REGS_START (WCN_DUMP_CP2_IRAM_END + 1)
#define WCN_DUMP_AP_REGS_END 9
/* CP2 regs start and end */
#define WCN_DUMP_CP2_REGS_START (WCN_DUMP_AP_REGS_END + 1)
#define WCN_DUMP_CP2_REGS_END (ARRAY_SIZE(s_wcn_dump_regs) - 1)

#define CP_START_ADDR		0
#define CP_RESET_REG		0x40060288
#define CP_SDIO_PRIORITY_ADDR 0x60300150
/* set sdio higher priority to visit iram */
#define M6_TO_S0_HIGH_PRIORITY 0X80000000
#define PACKET_SIZE		(32*1024)
#define CARD_DETECT_WAIT_MS	18000
#define POWERUP_WAIT_MS	30000	/* time out in waiting wifi to come up */
#define POWERUP_DELAY		200
#define RESET_DELAY		1
#define FIRMWARE_MAX_SIZE 0x90c00
#define WIFI_REG 0x60300004
#define CHIPID_REG 0x603003fc
#define CALI_REG 0x70040000
#define CALI_OFSET_REG 0x70040010
#define MARLIN2_AA_CHIPID 0x23490000
#define MARLIN2_AB_CHIPID 0x23490001

#define DUMP_WIFI_ADDR			0x70000000
#define DUMP_WIFI_ADDR_SIZE		0x70000

#define DUMP_BT_CMD_ADDR		0X50000000
#define DUMP_BT_CMD_ADDR_SIZE		0x400
#define DUMP_BT_ADDR			0X50040000
#define DUMP_BT_ADDR_SIZE		0xa400

#define DUMP_FM_ADDR			0X400B0000
#define DUMP_INTC_ADDR			0X40010000

#define DUMP_SYSTIMER_ADDR		0X40020000
#define DUMP_WDG_ADDR			0X40040000
#define DUMP_APB_ADDR			0X40060000
#define DUMP_DMA_ADDR			0X60200000
#define DUMP_AHB_ADDR			0X60300000
#define DUMP_REG_SIZE			0X10000
#define DUMP_SDIO_ADDR			0x60400000
#define DUMP_SDIO_ADDR_SIZE		0x10000

/* need check, not need to dump it */
#define DUMP_WIFI_1_ADDR            0
#define DUMP_WIFI_1_ADDR_SIZE        0
#define DUMP_WIFI_2_ADDR            0
#define DUMP_WIFI_2_ADDR_SIZE        0
#define DUMP_WIFI_3_ADDR            0
#define DUMP_WIFI_3_ADDR_SIZE        0

/* For GNSS */
#define GNSS_CP_START_ADDR	0x40A20000
#define GNSS_CP_RESET_REG	0x40BC8280
#define GNSS_FIRMWARE_MAX_SIZE 0x58000
#define GNSS_CHIPID_REG 0x603003fc

#endif
