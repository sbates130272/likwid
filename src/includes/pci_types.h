/*
 * =======================================================================================
 *
 *      Filename:  pci_types.h
 *
 *      Description:  Types file for pci module.
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


#ifndef PCI_TYPES_H
#define PCI_TYPES_H

#include <stdint.h>



typedef enum {
    NONE = 0,
    R3QPI,
    R2PCIE,
    IMC,
    HA,
    QPI,
    IRP,
    MAX_NUM_PCI_TYPES
} PciDeviceType;

typedef enum {
    MSR_DEV = 0,
    PCI_R3QPI_DEVICE_LINK_0,
    PCI_R3QPI_DEVICE_LINK_1,
    PCI_R3QPI_DEVICE_LINK_2,
    PCI_R2PCIE_DEVICE,
    PCI_IMC_DEVICE_0_CH_0,
    PCI_IMC_DEVICE_0_CH_1,
    PCI_IMC_DEVICE_0_CH_2,
    PCI_IMC_DEVICE_0_CH_3,
    PCI_HA_DEVICE_0,
    PCI_HA_DEVICE_1,
    PCI_QPI_DEVICE_PORT_0,
    PCI_QPI_DEVICE_PORT_1,
    PCI_QPI_DEVICE_PORT_2,
    PCI_QPI_MASK_DEVICE_PORT_0,
    PCI_QPI_MASK_DEVICE_PORT_1,
    PCI_QPI_MASK_DEVICE_PORT_2,
    PCI_QPI_MISC_DEVICE_PORT_0,
    PCI_QPI_MISC_DEVICE_PORT_1,
    PCI_QPI_MISC_DEVICE_PORT_2,
    PCI_IMC_DEVICE_1_CH_0,
    PCI_IMC_DEVICE_1_CH_1,
    PCI_IMC_DEVICE_1_CH_2,
    PCI_IMC_DEVICE_1_CH_3,
    PCI_IRP_DEVICE,
    MAX_NUM_PCI_DEVICES
} PciDeviceIndex;

typedef struct {
    PciDeviceType type;
    char *path;
    char *name;
    char *likwid_name;
    uint32_t devid;
    int  online;
} PciDevice;

typedef struct {
    char* name;
    char* desc;
} PciType;


static PciType pci_types[MAX_NUM_PCI_TYPES] = {
    [R3QPI] = {"R3QPI", "R3QPI is the interface between the Intel QPI Link Layer and the Ring."},
    [R2PCIE] = {"R2PCIE", "R2PCIe represents the interface between the Ring and IIO traffic to/from PCIe."},
    [IMC] = {"IMC", "The integrated Memory Controller provides the interface to DRAM and communicates to the rest of the uncore through the Home Agent."},
    [HA] = {"HA", "The HA is responsible for the protocol side of memory interactions."},
    [QPI] = {"QPI", "The Intel QPI Link Layer is responsible for packetizing requests from the caching agent on the way out to the system interface."},
    [IRP] = {"IRP", "IRP is responsible for maintaining coherency for IIO traffic e.g. crosssocket P2P."}
};
#endif /*PCI_TYPES_H*/
