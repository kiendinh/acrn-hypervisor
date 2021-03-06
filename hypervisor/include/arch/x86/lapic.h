/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INTR_LAPIC_H
#define INTR_LAPIC_H

#define DEBUG_LAPIC 0

enum intr_lapic_icr_delivery_mode {
	INTR_LAPIC_ICR_FIXED = 0x0,
	INTR_LAPIC_ICR_LP = 0x1,
	INTR_LAPIC_ICR_SMI = 0x2,
	INTR_LAPIC_ICR_NMI = 0x4,
	INTR_LAPIC_ICR_INIT = 0x5,
	INTR_LAPIC_ICR_STARTUP = 0x6,
};

enum intr_lapic_icr_dest_mode {
	INTR_LAPIC_ICR_PHYSICAL = 0x0,
	INTR_LAPIC_ICR_LOGICAL = 0x1
};

enum intr_lapic_icr_level {
	INTR_LAPIC_ICR_DEASSERT = 0x0,
	INTR_LAPIC_ICR_ASSERT = 0x1,
};

enum intr_lapic_icr_trigger {
	INTR_LAPIC_ICR_EDGE = 0x0,
	INTR_LAPIC_ICR_LEVEL = 0x1,
};

enum intr_lapic_icr_shorthand {
	INTR_LAPIC_ICR_USE_DEST_ARRAY = 0x0,
	INTR_LAPIC_ICR_SELF = 0x1,
	INTR_LAPIC_ICR_ALL_INC_SELF = 0x2,
	INTR_LAPIC_ICR_ALL_EX_SELF = 0x3,
};

/* Default LAPIC base */
#define LAPIC_BASE                              0xFEE00000

/* LAPIC register offset for memory mapped IO access */
#define LAPIC_ID_REGISTER                       0x00000020
#define LAPIC_VERSION_REGISTER                  0x00000030
#define LAPIC_TASK_PRIORITY_REGISTER            0x00000080
#define LAPIC_ARBITRATION_PRIORITY_REGISTER     0x00000090
#define LAPIC_PROCESSOR_PRIORITY_REGISTER       0x000000A0
#define LAPIC_EOI_REGISTER                      0x000000B0
#define LAPIC_REMOTE_READ_REGISTER              0x000000C0
#define LAPIC_LOGICAL_DESTINATION_REGISTER      0x000000D0
#define LAPIC_DESTINATION_FORMAT_REGISTER       0x000000E0
#define LAPIC_SPURIOUS_VECTOR_REGISTER          0x000000F0
#define LAPIC_IN_SERVICE_REGISTER_0             0x00000100
#define LAPIC_IN_SERVICE_REGISTER_1             0x00000110
#define LAPIC_IN_SERVICE_REGISTER_2             0x00000120
#define LAPIC_IN_SERVICE_REGISTER_3             0x00000130
#define LAPIC_IN_SERVICE_REGISTER_4             0x00000140
#define LAPIC_IN_SERVICE_REGISTER_5             0x00000150
#define LAPIC_IN_SERVICE_REGISTER_6             0x00000160
#define LAPIC_IN_SERVICE_REGISTER_7             0x00000170
#define LAPIC_TRIGGER_MODE_REGISTER_0           0x00000180
#define LAPIC_TRIGGER_MODE_REGISTER_1           0x00000190
#define LAPIC_TRIGGER_MODE_REGISTER_2           0x000001A0
#define LAPIC_TRIGGER_MODE_REGISTER_3           0x000001B0
#define LAPIC_TRIGGER_MODE_REGISTER_4           0x000001C0
#define LAPIC_TRIGGER_MODE_REGISTER_5           0x000001D0
#define LAPIC_TRIGGER_MODE_REGISTER_6           0x000001E0
#define LAPIC_TRIGGER_MODE_REGISTER_7           0x000001F0
#define LAPIC_INT_REQUEST_REGISTER_0            0x00000200
#define LAPIC_INT_REQUEST_REGISTER_1            0x00000210
#define LAPIC_INT_REQUEST_REGISTER_2            0x00000220
#define LAPIC_INT_REQUEST_REGISTER_3            0x00000230
#define LAPIC_INT_REQUEST_REGISTER_4            0x00000240
#define LAPIC_INT_REQUEST_REGISTER_5            0x00000250
#define LAPIC_INT_REQUEST_REGISTER_6            0x00000260
#define LAPIC_INT_REQUEST_REGISTER_7            0x00000270
#define LAPIC_ERROR_STATUS_REGISTER             0x00000280
#define LAPIC_LVT_CMCI_REGISTER                 0x000002F0
#define LAPIC_INT_COMMAND_REGISTER_0            0x00000300
#define LAPIC_INT_COMMAND_REGISTER_1            0x00000310
#define LAPIC_LVT_TIMER_REGISTER                0x00000320
#define LAPIC_LVT_THERMAL_SENSOR_REGISTER       0x00000330
#define LAPIC_LVT_PMC_REGISTER                  0x00000340
#define LAPIC_LVT_LINT0_REGISTER                0x00000350
#define LAPIC_LVT_LINT1_REGISTER                0x00000360
#define LAPIC_LVT_ERROR_REGISTER                0x00000370
#define LAPIC_INITIAL_COUNT_REGISTER            0x00000380
#define LAPIC_CURRENT_COUNT_REGISTER            0x00000390
#define LAPIC_DIVIDE_CONFIGURATION_REGISTER     0x000003E0

/* LAPIC CPUID bit and bitmask definitions */
#define CPUID_OUT_RDX_APIC_PRESENT              ((uint64_t) 1 <<  9)
#define CPUID_OUT_RCX_X2APIC_PRESENT            ((uint64_t) 1 << 21)

/* LAPIC MSR bit and bitmask definitions */
#define MSR_01B_XAPIC_GLOBAL_ENABLE             ((uint64_t) 1 << 11)

/* LAPIC register bit and bitmask definitions */
#define LAPIC_SVR_VECTOR                        0x000000FF
#define LAPIC_SVR_APIC_ENABLE_MASK                   0x00000100

#define LAPIC_LVT_MASK                          0x00010000
#define LAPIC_DELIVERY_MODE_EXTINT_MASK         0x00000700

/* LAPIC Timer bit and bitmask definitions */
#define LAPIC_TMR_ONESHOT                       ((uint32_t) 0x0 << 17)
#define LAPIC_TMR_PERIODIC                      ((uint32_t) 0x1 << 17)
#define LAPIC_TMR_TSC_DEADLINE                  ((uint32_t) 0x2 << 17)

enum intr_cpu_startup_shorthand {
	INTR_CPU_STARTUP_USE_DEST,
	INTR_CPU_STARTUP_ALL_EX_SELF,
	INTR_CPU_STARTUP_UNKNOWN,
};

union lapic_id {
	uint32_t value;
	struct {
		uint8_t xapic_id;
		uint8_t rsvd[3];
	} xapic;
	union {
		uint32_t value;
		struct {
			uint8_t xapic_id;
			uint8_t xapic_edid;
			uint8_t rsvd[2];
		} ioxapic_view;
		struct {
			uint32_t x2apic_id:4;
			uint32_t x2apic_cluster:28;
		} ldr_view;
	} x2apic;
};

struct lapic_regs {
	uint32_t id;
	uint32_t tpr;
	uint32_t apr;
	uint32_t ppr;
	uint32_t ldr;
	uint32_t dfr;
	uint32_t tmr[8];
	uint32_t svr;
	uint32_t lvtt;
	uint32_t lvt0;
	uint32_t lvt1;
	uint32_t lvterr;
	uint32_t ticr;
	uint32_t tccr;
	uint32_t tdcr;
};

void write_lapic_reg32(uint32_t offset, uint32_t value);
void save_lapic(struct lapic_regs *regs);
int early_init_lapic(void);
int init_lapic(uint32_t cpu_id);
int send_lapic_eoi(void);
uint32_t get_cur_lapic_id(void);
int send_startup_ipi(enum intr_cpu_startup_shorthand cpu_startup_shorthand,
		uint32_t cpu_startup_dest,
		uint64_t cpu_startup_start_address);
/* API to send an IPI to a single guest */
void send_single_ipi(uint32_t pcpu_id, uint32_t vector);

#endif /* INTR_LAPIC_H */
