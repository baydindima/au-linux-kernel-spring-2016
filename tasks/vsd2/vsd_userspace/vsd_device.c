#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../vsd_driver/vsd_ioctl.h"
#include "vsd_device.h"

static int vsd_descriptor;

int get_vsd_descriptor() {
    return open("/dev/vsd", O_RDWR);
}

int vsd_init() {
    vsd_descriptor = get_vsd_descriptor();
    // printf("File descriptor is %d\n", vsd_descriptor);
    return vsd_descriptor == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int vsd_deinit() {
    close(vsd_descriptor);
    return EXIT_SUCCESS;
}

int vsd_get_size(size_t *out_size) {
    // printf("File descriptor is %d\n", vsd_descriptor);
    vsd_ioctl_get_size_arg_t size;
    int result = ioctl(vsd_descriptor, VSD_IOCTL_GET_SIZE, &size);
    // printf("Size is %zu\n", size.size);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    *out_size = size.size;
    return EXIT_SUCCESS;
}

int vsd_set_size(size_t size) {
    vsd_ioctl_set_size_arg_t new_size;
    new_size.size = size;
    int result = ioctl(vsd_descriptor, VSD_IOCTL_SET_SIZE, &new_size);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

ssize_t vsd_read(char* dst, off_t offset, size_t size) {
    if(lseek(vsd_descriptor, offset, SEEK_SET) < 0) return -1;
    return read(vsd_descriptor, dst, size);
}

ssize_t vsd_write(const char* src, off_t offset, size_t size) {
    if(lseek(vsd_descriptor, offset, SEEK_SET) < 0) return -1;
    return write(vsd_descriptor, src, size);
}

void* vsd_mmap(size_t offset) {
    size_t len;
    vsd_get_size(&len);
    return mmap(0, len - offset, PROT_READ | PROT_WRITE, MAP_SHARED, vsd_descriptor, offset);
}

int vsd_munmap(void* addr, size_t offset) {
    size_t len;
    vsd_get_size(&len);
    return munmap(addr, len - offset);
}
