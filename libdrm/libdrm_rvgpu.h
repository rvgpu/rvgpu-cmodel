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

#ifndef __LIBDRM_RVGPU_H__
#define __LIBDRM_RVGPU_H__

int rvgpu_drmIoctl(int fd, unsigned long request, void *arg);
int rvgpu_drmOpen(const char *name, const char *busid);
int rvgpu_drmGetDevices2(uint32_t flags, drmDevicePtr devices[], int max_devices);
int rvgpu_drmGetDevice2(int fd, uint32_t flags, drmDevicePtr *device);
void rvgpu_drmFreeDevice(drmDevicePtr *device);
void rvgpu_drmFreeDevices(drmDevicePtr devices[], int count);
drmVersionPtr rvgpu_drmGetVersion(int fd);
void rvgpu_drmFreeVersion(drmVersionPtr versionptr);
int rvgpu_drmSyncobjCreate(int fd, uint32_t flags, uint32_t *handle);
int rvgpu_drmSyncobjWait(int fd, uint32_t *handles, unsigned num_handles, int64_t timeout_nsec, unsigned flags, uint32_t *first_signaled);
int rvgpu_drmSyncobjDestroy(int fd, uint32_t handle);
int rvgpu_drmGetCap(int fd, uint64_t capability, uint64_t *value);
int rvgpu_drmAuthMagic(int fd, drm_magic_t magic);
int rvgpu_drmSyncobjReset(int fd, const uint32_t *handles, uint32_t handle_count);
int rvgpu_drmSyncobjTimelineWait(int fd, uint32_t *handles, uint64_t *points, unsigned num_handles, int64_t timeout_nsec, unsigned flags, uint32_t *first_signaled);

#endif // __LIBDRM_RVGPU_H__
