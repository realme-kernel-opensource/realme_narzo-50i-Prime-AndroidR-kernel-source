/*
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * MyungJoo.Ham <myungjoo.ham@samsung.com>
 *
 * Charger Manager.
 * This framework enables to control and multiple chargers and to
 * monitor charging even in the context of suspend-to-RAM with
 * an interface combining the chargers.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
**/

#ifndef _CHARGER_MANAGER_H
#define _CHARGER_MANAGER_H

#include <linux/alarmtimer.h>
#include <linux/extcon.h>
#include <linux/power_supply.h>
#include <linux/power/sprd_vote.h>
typedef enum {
	CHARGER_SUBTYPE_DEFAULT = 0,
	CHARGER_SUBTYPE_FASTCHG_VOOC,
	CHARGER_SUBTYPE_FASTCHG_SVOOC,
	CHARGER_SUBTYPE_PD,
	CHARGER_SUBTYPE_QC,
	CHARGER_SUBTYPE_PE20
}OPLUS_CHARGER_SUBTYPE;

enum power_supply_charger_type {
	POWER_SUPPLY_CHARGER_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_USB_CHARGER_TYPE_SDP,		/* Standard Downstream Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_DCP,		/* Dedicated Charging Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_CDP,		/* Charging Downstream Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_ACA,		/* Accessory Charger Adapters */
	POWER_SUPPLY_USB_CHARGER_TYPE_C,		/* Type C Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_PD,		/* Power Delivery Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_PD_DRP,		/* PD Dual Role Port */
	POWER_SUPPLY_USB_CHARGER_TYPE_PD_PPS,		/* PD Programmable Power Supply */
	POWER_SUPPLY_USB_CHARGER_TYPE_APPLE_BRICK_ID,	/* Apple Charging Method */
	POWER_SUPPLY_USB_CHARGER_TYPE_SFCP_1P0,		/* SFCP1.0 Port*/
	POWER_SUPPLY_USB_CHARGER_TYPE_SFCP_2P0,		/* SFCP2.0 Port*/
	POWER_SUPPLY_WIRELESS_CHARGER_TYPE_BPP,		/* BPP wireless method */
	POWER_SUPPLY_WIRELESS_CHARGER_TYPE_EPP,		/* EPP wiresess method */
};

enum cm_charge_info_cmd {
	CM_CHARGE_INFO_CHARGE_LIMIT = BIT(0),
	CM_CHARGE_INFO_INPUT_LIMIT = BIT(1),
	CM_CHARGE_INFO_THERMAL_LIMIT = BIT(2),
	CM_CHARGE_INFO_JEITA_LIMIT = BIT(3),
};

enum data_source {
	CM_BATTERY_PRESENT,
	CM_NO_BATTERY,
	CM_FUEL_GAUGE,
	CM_CHARGER_STAT,
};

enum polling_modes {
	CM_POLL_DISABLE = 0,
	CM_POLL_ALWAYS,
	CM_POLL_EXTERNAL_POWER_ONLY,
	CM_POLL_CHARGING_ONLY,
};

enum cm_event_types {
	CM_EVENT_UNKNOWN = 0,
	CM_EVENT_BATT_FULL,
	CM_EVENT_BATT_IN,
	CM_EVENT_BATT_OUT,
	CM_EVENT_BATT_OVERHEAT,
	CM_EVENT_BATT_COLD,
	CM_EVENT_EXT_PWR_IN_OUT,
	CM_EVENT_CHG_START_STOP,
	CM_EVENT_FAST_CHARGE,
	CM_EVENT_INT,
	CM_EVENT_OTHERS,
};

enum cm_jeita_types {
	CM_JEITA_DCP = 0,
	CM_JEITA_SDP,
	CM_JEITA_CDP,
	CM_JEITA_UNKNOWN,
	CM_JEITA_FCHG,
	CM_JEITA_MAX,
};

enum cm_capacity_cmd {
	CM_CAPACITY = 0,
	CM_BOOT_CAPACITY,
};

enum cm_charge_status {
	CM_CHARGE_TEMP_OVERHEAT = BIT(0),
	CM_CHARGE_TEMP_COLD = BIT(1),
	CM_CHARGE_VOLTAGE_ABNORMAL = BIT(2),
	CM_CHARGE_HEALTH_ABNORMAL = BIT(3),
	CM_CHARGE_DURATION_ABNORMAL = BIT(4),
};

enum cm_fast_charge_command {
	CM_FAST_CHARGE_NORMAL_CMD = 1,
	CM_FAST_CHARGE_ENABLE_CMD,
	CM_FAST_CHARGE_DISABLE_CMD,
};

struct wireless_data {
	struct power_supply_desc psd;
	struct power_supply *psy;
	int WIRELESS_ONLINE;
};

struct ac_data {
	struct power_supply_desc psd;
	struct power_supply *psy;
	int AC_ONLINE;
};

struct usb_data {
	struct power_supply_desc psd;
	struct power_supply *psy;
	int USB_ONLINE;
};

/**
 * struct charger_cable
 * @extcon_name: the name of extcon device.
 * @name: the name of charger cable(external connector).
 * @extcon_dev: the extcon device.
 * @wq: the workqueue to control charger according to the state of
 *	charger cable. If charger cable is attached, enable charger.
 *	But if charger cable is detached, disable charger.
 * @nb: the notifier block to receive changed state from EXTCON
 *	(External Connector) when charger cable is attached/detached.
 * @attached: the state of charger cable.
 *	true: the charger cable is attached
 *	false: the charger cable is detached
 * @charger: the instance of struct charger_regulator.
 * @cm: the Charger Manager representing the battery.
 */
struct charger_cable {
	const char *extcon_name;
	const char *name;

	/* The charger-manager use Extcon framework */
	struct extcon_dev *extcon_dev;
	struct notifier_block nb;

	/* The state of charger cable */
	bool attached;

	struct charger_regulator *charger;

	/*
	 * Set min/max current of regulator to protect over-current issue
	 * according to a kind of charger cable when cable is attached.
	 */
	int min_uA;
	int max_uA;

	struct charger_manager *cm;
};

/**
 * struct charger_regulator
 * @regulator_name: the name of regulator for using charger.
 * @consumer: the regulator consumer for the charger.
 * @externally_control:
 *	Set if the charger-manager cannot control charger,
 *	the charger will be maintained with disabled state.
 * @cables:
 *	the array of charger cables to enable/disable charger
 *	and set current limit according to constraint data of
 *	struct charger_cable if only charger cable included
 *	in the array of charger cables is attached/detached.
 * @num_cables: the number of charger cables.
 * @attr_g: Attribute group for the charger(regulator)
 * @attr_name: "name" sysfs entry
 * @attr_state: "state" sysfs entry
 * @attr_externally_control: "externally_control" sysfs entry
 * @attr_jeita_control: "jeita_control" sysfs entry
 * @attrs: Arrays pointing to attr_name/state/externally_control for attr_g
 */
struct charger_regulator {
	/* The name of regulator for charging */
	const char *regulator_name;
	struct regulator *consumer;

	/* charger never on when system is on */
	int externally_control;

	/*
	 * Store constraint information related to current limit,
	 * each cable have different condition for charging.
	 */
	struct charger_cable *cables;
	int num_cables;

	struct attribute_group attr_g;
	struct device_attribute attr_name;
	struct device_attribute attr_state;
	struct device_attribute attr_stop_charge;
	struct device_attribute attr_externally_control;
	struct device_attribute attr_jeita_control;
	struct attribute *attrs[6];

	struct charger_manager *cm;
};

struct charger_jeita_table {
	int temp;
	int recovery_temp;
	int current_ua;
	int term_volt;
	int step_chg_cur;
	int step_chg_volt;
};

#define CM_IBAT_BUFF_CNT                    7
/*
 * struct cm_ir_compensation
 * @us: record the full charged battery voltage at normal condition.
 * @rc: compensation resistor value in mohm
 * @ibat_buf: record battery current
 * @us_upper_limit: limit the max battery voltage
 * @cp_upper_limit_offset: use for charge pump mode to adjust battery over
 *	voltage protection value.
 * @us_lower_limit: record the min battery voltage
 * @ir_compensation_en: enable/disable current and resistor compensation function.
 * ibat_index: record current battery current in the ibat_buf
 * @last_target_cccv: record last target cccv point;
 */
struct cm_ir_compensation {
	int us;
	int rc;
	int ibat_buf[CM_IBAT_BUFF_CNT];
	int us_upper_limit;
	int us_lower_limit;
	bool ir_compensation_en;
	int ibat_index;
	int last_target_cccv;
};

/*
 * struct cap_remap_table
 * @cnt: record the counts of battery capacity of this scope
 * @lcap: the lower boundary of the capacity scope before transfer
 * @hcap: the upper boundary of the capacity scope before transfer
 * @lb: the lower boundary of the capacity scope after transfer
 * @hb: the upper boundary of the capacity scope after transfer
*/
struct cap_remap_table {
	int cnt;
	int lcap;
	int hcap;
	int lb;
	int hb;
};

/**
 * struct charger_desc
 * @psy_name: the name of power-supply-class for charger manager
 * @polling_mode:
 *	Determine which polling mode will be used
 * @fullbatt_vchkdrop_ms:
 * @fullbatt_vchkdrop_uV:
 *	Check voltage drop after the battery is fully charged.
 *	If it has dropped more than fullbatt_vchkdrop_uV after
 *	fullbatt_vchkdrop_ms, CM will restart charging.
 * @fullbatt_uV: voltage in microvolt
 *	If VBATT >= fullbatt_uV, it is assumed to be full.
 * @fullbatt_uA: battery current in microamp
 * @first_fullbatt_uA: battery current in microamp of first_full charged
 * @fullbatt_soc: state of Charge in %
 *	If state of Charge >= fullbatt_soc, it is assumed to be full.
 * @fullbatt_full_capacity: full capacity measure
 *	If full capacity of battery >= fullbatt_full_capacity,
 *	it is assumed to be full.
 * @polling_interval_ms: interval in millisecond at which
 *	charger manager will monitor battery health
 * @battery_present:
 *	Specify where information for existence of battery can be obtained
 * @psy_charger_stat: the names of power-supply for chargers
 * @psy_fast_charger_stat: the names of power-supply for fast chargers
 * @psy_cp_stat: the names of power-supply for charge pumps
 * @psy_wl_charger_stat: the names of power-supply for wireless chargers
 * @psy_cp_converter_stat: the names of power-supply for charge pump converters
 * @num_charger_regulator: the number of entries in charger_regulators
 * @charger_regulators: array of charger regulators
 * @psy_fuel_gauge: the name of power-supply for fuel gauge
 * @thermal_zone : the name of thermal zone for battery
 * @temp_min : Minimum battery temperature for charging.
 * @temp_max : Maximum battery temperature for charging.
 * @temp_diff : Temperature difference to restart charging.
 * @cap : Battery capacity report to user space.
 * @measure_battery_temp:
 *	true: measure battery temperature
 *	false: measure ambient temperature
 * @charging_max_duration_ms: Maximum possible duration for charging
 *	If whole charging duration exceed 'charging_max_duration_ms',
 *	cm stop charging.
 * @discharging_max_duration_ms:
 *	Maximum possible duration for discharging with charger cable
 *	after full-batt. If discharging duration exceed 'discharging
 *	max_duration_ms', cm start charging.
 * @normal_charge_voltage_max:
 *	maximum normal charge voltage in microVolts
 * @normal_charge_voltage_drop:
 *	drop voltage in microVolts to allow restart normal charging
 * @fast_charge_voltage_max:
 *	maximum fast charge voltage in microVolts
 * @fast_charge_voltage_drop:
 *	drop voltage in microVolts to allow restart fast charging
 * @flash_charge_voltage_max:
 *	maximum flash charge voltage in microVolts
 * @flash_charge_voltage_drop:
 *	drop voltage in microVolts to allow restart flash charging
 * @wireless_normal_charge_voltage_max:
 *	maximum wireless normal charge voltage in microVolts
 * @wireless_normal_charge_voltage_drop:
 *	drop voltage in microVolts to allow restart wireless charging
 * @wireless_fast_charge_voltage_max:
 *	maximum wireless fast charge voltage in microVolts
 * @wireless_fast_charge_voltage_drop:
 *	drop voltage in microVolts to allow restart wireless fast charging
 * @charger_status: Recording state of charge
 * @charger_type: Recording type of charge
 * @first_trigger_cnt: The number of times the battery is first_fully charged
 * @trigger_cnt: The number of times the battery is fully charged
 * @uvlo_trigger_cnt: The number of times the battery voltage is
 *	less than under voltage lock out
 * @low_temp_trigger_cnt: The number of times the battery temperature
 *	is less than 10 degree.
 * @cap_one_time: The percentage of electricity is not
 *	allowed to change by 1% in cm->desc->cap_one_time
 * @trickle_time_out: If 99% lasts longer than it , will force set full statu
 * @trickle_time: Record the charging time when battery
 *	capacity is larger than 99%.
 * @trickle_start_time: Record current time when battery capacity is 99%
 * @update_capacity_time: Record the battery capacity update time
 * @last_query_time: Record last time enter cm_batt_works
 * @force_set_full: The flag is indicate whether
 *	there is a mandatory setting of full status
 * @shutdown_voltage: If it has dropped more than shutdown_voltage,
 *	the phone will automatically shut down
 * @wdt_interval: Watch dog time pre-load value
 * @jeita_tab: Specify the jeita temperature table, which is used to
 *	adjust the charging current according to the battery temperature.
 * @jeita_tab_size: Specify the size of jeita temperature table.
 * @jeita_tab_array: Specify the jeita temperature table array, which is used to
 *	save the point of adjust the charging current according to the battery temperature.
 * @jeita_disabled: disable jeita function when needs
 * @force_jeita_status: force jeita to this status when disable jeita
 * @temperature: the battery temperature
 * @internal_resist: the battery internal resistance in mOhm
 * @cap_table_len: the length of ocv-capacity table
 * @cap_table: capacity table with corresponding ocv
 * @cap_remap_table: the table record the different scope of capacity
 *	information.
 * @cap_remap_table_len: the length of cap_remap_table
 * @cap_remap_total_cnt: the total count the whole battery capacity is divided
	into.
 * @is_fast_charge: if it is support fast charge or not
 * @enable_fast_charge: if is it start fast charge or not
 * @fast_charge_enable_count: to count the number that satisfy start
 *	fast charge condition.
 * @fast_charge_disable_count: to count the number that satisfy stop
 *	fast charge condition.
 * @double_IC_total_limit_current: if it use two charge IC to support
 *	fast charge, we use total limit current to campare with thermal_val,
 *	to limit the thermal_val under total limit current.
 * @cm_check_int: record the intterupt event
 * @cm_check_fault: record the flag whether need to check fault status
 * @fast_charger_type: record the charge type
 * @cp: record the charge pump status
 * @ir_comp: record the current and resistor compensation status
 * @wl_charge_en: if it is wireless charge enabled or not
 * @usb_charge_en: if it is usb charge enabled or not
 * @adapter_default_charge_vol(v): adapter charge voltage for thermal to calculate
 *     input limit current
 */
struct charger_desc {
	const char *psy_name;

	enum polling_modes polling_mode;
	unsigned int polling_interval_ms;

	unsigned int fullbatt_vchkdrop_ms;
	unsigned int fullbatt_vchkdrop_uV;
	unsigned int fullbatt_uV;
	unsigned int fullbatt_uA;
	unsigned int fullbatt_soc;
	unsigned int fullbatt_full_capacity;

	enum data_source battery_present;

	const char **psy_charger_stat;
	const char **psy_fast_charger_stat;

	int num_charger_regulators;
	struct charger_regulator *charger_regulators;

	const char *psy_fuel_gauge;

	const char *thermal_zone;

	int temp_min;
	int temp_max;
	int temp_diff;

	int cap;
	bool measure_battery_temp;

	u32 charging_max_duration_ms;
	u32 discharging_max_duration_ms;

	u32 charge_voltage_max;
	u32 charge_voltage_drop;
	u32 normal_charge_voltage_max;
	u32 normal_charge_voltage_drop;
	u32 fast_charge_voltage_max;
	u32 fast_charge_voltage_drop;

	int charger_status;
	u32 charger_type;
	int trigger_cnt;
	int low_temp_trigger_cnt;
	int uvlo_trigger_cnt;

	u32 cap_one_time;

	u32 trickle_time_out;
	u64 trickle_time;
	u64 trickle_start_time;

	u64 update_capacity_time;
	u64 last_query_time;

	u64 charger_safety_time;
	u64 chg_uicap100_time;
	int cap_timing_en;
	int chg_uicap100_timeout;
	int now_ui_cap;
	int chg_status_now;
	bool battery_is_full;
	bool battery_is_uvlo;

	bool force_set_full;
	u32 shutdown_voltage;

	u32 wdt_interval;

	int thm_adjust_cur;

	struct charger_jeita_table *jeita_tab;
	u32 jeita_tab_size;
	u32 jeita_size[CM_JEITA_MAX];
	struct charger_jeita_table *jeita_tab_array[CM_JEITA_MAX];
	bool fchg_jeita_restore;

	bool jeita_disabled;
	int force_jeita_status;

	int temperature;

	int internal_resist;
	int cap_table_len;
	struct power_supply_battery_ocv_table *cap_table;
	struct cap_remap_table *cap_remap_table;
	u32 cap_remap_table_len;
	int cap_remap_total_cnt;
	bool is_fast_charge;
	bool enable_fast_charge;
	bool fixed_fchg_running;
	bool wait_vbus_stable;
	bool check_fixed_fchg_threshold;
	bool force_pps_diasbled;
	u32 fast_charge_enable_count;
	u32 fast_charge_disable_count;
	u32 double_ic_total_limit_current;
	bool authenticate;
	int thermal_fchg_support;
	
	struct cm_ir_compensation ir_comp;
};

#define PSY_NAME_MAX	30

/**
 * struct charger_manager
 * @entry: entry for list
 * @dev: device pointer
 * @desc: instance of charger_desc
 * @fuel_gauge: power_supply for fuel gauge
 * @charger_stat: array of power_supply for chargers
 * @tzd_batt : thermal zone device for battery
 * @charger_enabled: the state of charger
 * @fullbatt_vchk_jiffies_at:
 *	jiffies at the time full battery check will occur.
 * @fullbatt_vchk_work: work queue for full battery check
 * @uvlo_work: work queue to check uvlo state
 * @ir_compensation_work: work queue to check current and resistor
 *	compensation state
 * @emergency_stop:
 *	When setting true, stop charging
 * @psy_name_buf: the name of power-supply-class for charger manager
 * @charger_psy: power_supply for charger manager
 * @status_save_ext_pwr_inserted:
 *	saved status of external power before entering suspend-to-RAM
 * @status_save_batt:
 *	saved status of battery before entering suspend-to-RAM
 * @charging_start_time: saved start time of enabling charging
 * @charging_end_time: saved end time of disabling charging
 * @charging_status: saved charging status, 0 means charging normal
 * @battery_status: Current battery status
 * @charge_ws: wakeup source to prevent ap enter sleep mode in charge
 *	pump mode
 */
struct charger_manager {
	struct list_head entry;
	struct device *dev;
	struct charger_desc *desc;

#ifdef CONFIG_THERMAL
	struct thermal_zone_device *tzd_batt;
#endif
	bool charger_enabled;

	unsigned long fullbatt_vchk_jiffies_at;
	struct delayed_work fullbatt_vchk_work;
	struct delayed_work cap_update_work;
	struct delayed_work uvlo_work;
	struct delayed_work ir_compensation_work;
	struct delayed_work fchg_check_work;
	struct delayed_work set_sec_current_work;
	struct delayed_work first_set_limit_work;
	int emergency_stop;

	char psy_name_buf[PSY_NAME_MAX + 1];
	struct power_supply_desc charger_psy_desc;
	struct power_supply *charger_psy;

	u64 charging_start_time;
	u64 charging_end_time;
	u32 charging_status;
	int capacity_control;
	int ato_input_limit;
	int mmi_chg;
};

#define BAT_COUNT                           2
int get_now_battery_id(void);
extern int get_battery_id(void);

#ifdef CONFIG_CHARGER_MANAGER
extern void cm_notify_event(struct power_supply *psy,
				enum cm_event_types type, char *msg);
#else
static inline void cm_notify_event(struct power_supply *psy,
				enum cm_event_types type, char *msg) { }
#endif
extern void get_charger_ic_reg_info(char *reg_info);
enum {
	BAT_OVP_SET = 0,
	FRAMEWORK_SET,
	MMI_SET,
	AGING_SET,
	ATO_SET,
	OVER_JEITA_TEMP_LIMIT,
	VBUS_OVP,
	BAT_POOR_CONTACT,
	BELOW_JEITA_TEMP_LIMIT,
	SAFETY_TIMER,
	HIZ_SET,
	HIGH_LOW_TEMP_SET,
	OTHERS_MAX,
};

#define CHG_VOL_OFFSET                      150000
#define CHG_VOL_OFFSET_MAX                  580000
#define CHG_LINE_IMPEDANCE                  127
#define BQ2560X_VINDPM                      4600
#define CM_WORK_TEMP_MAX                    850
#define BATTERY_VOLTAGE_MAX                 4550000
#define BATTERY_RECHARGE_VOLTAGE            4370000

#define CM_BAT_OVP_STATUS                   (1 << 0)
#define CM_STOP_CHARGE_NODE_STATUS          (1 << 1)
#define CM_ATO_MMI_TEST_STATUS              (1 << 2)
#define CM_AGING_CHARGE_STATUS              (1 << 3)
#define CM_ATO_CHARGE_STATUS                (1 << 4)
#define CM_OVER_JEITA_TEMP_LIMIT            (1 << 5)
#define CM_VBUS_OVP_STATUS                  (1 << 6)
#define CM_BATT_POOR_CONTACT                (1 << 7)
#define CM_BELOW_JEITA_TEMP_LIMIT           (1 << 8)
#define CM_CHARGER_SAFETY_TIMER             (1 << 9)
#define CM_CHARGER_HIZ_STATUS               (1 << 10)
#define CM_HIGH_LOW_TEMP_CHG_CTRL           (1 << 11)

#define MAX_INPUT_LIMIT_CURRENT             2200000
#define MAX_CHARGER_CURRENT                 2200000

#define CM_HIGH_TEMP_LEDON_CURRENT_MAX      500000
#define CM_HIGH_TEMP_LEDOFF_CURRENT_MAX     1425000
#define CM_THERMAL_2000MA                   2000000
#define CM_THERMAL_1000MA                   1000000
#define CM_THERMAL_500MA                    500000

#define CM_MAIN_CHARGER_CURRENT_RATIO       5
#define CM_SECOND_CHARGER_CURRENT_RATIO     5

#define FCHG_CHECK_WORK_TIME                1
#define FCHG_CHECK_WORK_COUNT               5

#define CM_WAIT_HVDCP_SUCC_COUNT            5
#define SET_SECOND_CURRENT_TIMER            1

#define CM_RESTORE_BATT_VOL_SHAKE           4000000
#define CM_BATTERY_CV_VOL_4432MV            4432000
#define CM_BATTERY_CV_VOL_3980MV            3980000
#define CM_BATTERY_CV_VOL_4112MV            4112000

#define CM_CAP100_TIMEOUT_TIME              1200

#define BAT_TEMP_ABNORMAL                   (-350)
#endif /* _CHARGER_MANAGER_H */
