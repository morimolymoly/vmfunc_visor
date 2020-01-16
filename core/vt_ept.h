/*
 * Copyright (c) 2007, 2008 University of Tsukuba
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Tsukuba nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CORE_VT_EPT_H
#define _CORE_VT_EPT_H

#define NUM_OF_EPTBL	1024
#define EPTE_READ	0x1
#define EPTE_READEXEC	0x5
#define EPTE_WRITE	0x2
#define EPTE_LARGE	0x80
#define EPTE_ATTR_MASK	0xFFF
#define EPTE_MT_SHIFT	3
#define EPT_LEVELS	4


#include "types.h"

#include "asm.h"
#include "constants.h"
#include "convert.h"
#include "current.h"
#include "gmm_access.h"
#include "mm.h"
#include "panic.h"
#include "string.h"
#include "vt_ept.h"
#include "vt_main.h"
#include "vt_paging.h"
#include "vt_regs.h"

struct vcpu;

struct vt_ept {
	int cnt;
	int cleared;
	void *ncr3tbl;
	phys_t ncr3tbl_phys;
	void *tbl[NUM_OF_EPTBL];
	phys_t tbl_phys[NUM_OF_EPTBL];
	void *tbl2[NUM_OF_EPTBL];
	phys_t tbl_phys2[NUM_OF_EPTBL];
	struct {
		int level;
		phys_t gphys;
		u64 *entry[EPT_LEVELS];
	} cur;

	struct vt_ept *ept2;

	__attribute__ ((aligned (4096))) u64 ptr_list[2];
};

void vt_ept_init (void);
void vt_ept_violation (bool write, u64 gphys);
void vt_ept_tlbflush (void);
void vt_ept_updatecr3 (void);
void vt_ept_clear_all (void);
bool vt_ept_extern_mapsearch (struct vcpu *p, phys_t start, phys_t end);
void vt_ept_map_1mb (void);
#endif
