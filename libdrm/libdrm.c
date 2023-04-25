/*
 * Copyright © 2023 Sietium Semiconductor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <xf86drm.h>
#include <stdlib.h>
#include <string.h>

int drmOpen(const char *name, const char *busid)
{
    return 0x123;
}

int drmGetDevices2(uint32_t flags, drmDevicePtr devices[], int max_devices)
{
    drmDevicePtr rvgsim_device;
    if (max_devices < 1) {
        return 0;
    }

    rvgsim_device = malloc(sizeof(drmDevice));

    rvgsim_device->nodes = malloc(sizeof(char *) * DRM_NODE_MAX);
    rvgsim_device->nodes[DRM_NODE_PRIMARY] = "rvgsim-primary";
    rvgsim_device->nodes[DRM_NODE_CONTROL] = "rvgsim-control";
    rvgsim_device->nodes[DRM_NODE_RENDER] = "rvgsim-render";

    /* set to DRM_NODE_RENDER */
    rvgsim_device->available_nodes = 1 << DRM_NODE_RENDER;
    rvgsim_device->bustype = DRM_BUS_PCI;

    /* use PCI device here */
    rvgsim_device->businfo.pci = malloc(sizeof(drmPciBusInfo));
    memset(rvgsim_device->businfo.pci, 0x0, sizeof(drmPciBusInfo));
    rvgsim_device->deviceinfo.pci = malloc(sizeof(drmPciDeviceInfo));
    memset(rvgsim_device->deviceinfo.pci, 0x0, sizeof(drmPciDeviceInfo));
    rvgsim_device->deviceinfo.pci->vendor_id = 0x16c3;
    rvgsim_device->deviceinfo.pci->device_id = 0x0001;

    devices[0] = rvgsim_device;

    // return the number of devices
    return 1;
}

int drmGetDevice2(int fd, uint32_t flags, drmDevicePtr *device)
{
    return drmGetDevices2(0, device, 1);
}

void drmFreeDevice(drmDevicePtr *device)
{
    if (*device) {
        free(*device);
    }
}

void drmFreeDevices(drmDevicePtr devices[], int count)
{
    for (int32_t i=0; i<count; i++) {
        drmFreeDevice(&devices[i]);
    }
}
