/*
 * =======================================================================================
 *
 *      Filename:  numa.c
 *
 *      Description:  Implementation of Linux NUMA interface
 *
 *      Version:   <VERSION>
 *      Released:  <DATE>
 *
 *      Author:  Jan Treibig (jt), jan.treibig@gmail.com
 *      Project:  likwid
 *
 *      Copyright (C) 2013 Jan Treibig 
 *
 *      This program is free software: you can redistribute it and/or modify it under
 *      the terms of the GNU General Public License as published by the Free Software
 *      Foundation, either version 3 of the License, or (at your option) any later
 *      version.
 *
 *      This program is distributed in the hope that it will be useful, but WITHOUT ANY
 *      WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 *      PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License along with
 *      this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * =======================================================================================
 */
/* #####   HEADER FILE INCLUDES   ######################################### */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <dirent.h>
#ifdef HAS_MEMPOLICY
#include <linux/mempolicy.h>
#endif
#include <topology.h>

#include <error.h>
#include <bstrlib.h>
#include <strUtil.h>

#include <numa.h>
#include <numa_proc.h>

#ifdef LIKWID_USE_HWLOC
#include <hwloc.h>
#include <topology_hwloc.h>
#include <numa_hwloc.h>
#endif


/* #####   EXPORTED VARIABLES   ########################################### */
NumaTopology numa_info = {0,NULL};
int maxIdConfiguredNode = 0;

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ######################### */
/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ###################### */
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ########### */
/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################## */

int
empty_numa_init()
{
    printf("MEMPOLICY NOT supported in kernel!\n");
}

void 
empty_numa_setInterleaved(int* processorList, int numberOfProcessors)
{
    printf("MEMPOLICY NOT supported in kernel!\n");
}

void
empty_numa_membind(void* ptr, size_t size, int domainId)
{
    printf("MBIND NOT supported in kernel!\n");
}


const struct numa_functions numa_funcs = {
#ifndef HAS_MEMPOLICY
    .numa_init = empty_numa_init,
    .numa_setInterleaved = empty_numa_setInterleaved,
    .numa_membind = empty_numa_membind
#else
#ifdef LIKWID_USE_HWLOC
    .numa_init = hwloc_numa_init,
    .numa_setInterleaved = hwloc_numa_setInterleaved,
    .numa_membind = hwloc_numa_membind
#else
    .numa_init = proc_numa_init,
    .numa_setInterleaved = proc_numa_setInterleaved,
    .numa_membind = proc_numa_membind
#endif
#endif
};


int numa_init(void)
{
    const struct numa_functions funcs = numa_funcs;
    return funcs.numa_init();
}

void numa_setInterleaved(int* processorList, int numberOfProcessors)
{
    const struct numa_functions funcs = numa_funcs;
    return funcs.numa_setInterleaved(processorList, numberOfProcessors);
}

void numa_membind(void* ptr, size_t size, int domainId)
{
    const struct numa_functions funcs = numa_funcs;
    return funcs.numa_membind(ptr, size, domainId);
}



