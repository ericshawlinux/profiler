#ifndef PFR_DISK_DEFINED
#define PFR_DISK_DEFINED

#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int pfr_disk_read(int fd, void *target_struct, int target_size, void **flex_value, int flex_size, const char *err_id)
{
    int read_size_a = 0, read_size_b = 0;
    
    read_size_a = read(fd, target_struct, target_size);
    
    if (read_size_a == -1)
        fprintf(stderr, "Error reading %s structure data: %s\n", err_id, strerror(errno));
    
    if (read_size_a != target_size)
        return 0;
    
    *flex_value = realloc(*flex_value, flex_size);
    
    if (*flex_value == NULL) {
        fprintf(stderr, "Error allocating memory for %s flexible value: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    read_size_b = read(fd, *flex_value, flex_size);
    
    if (read_size_b == -1)
        fprintf(stderr, "Error reading %s flexible value: %s\n", err_id, strerror(errno));
    
    if (read_size_b != flex_size)
        return 0;
    
    return 1;
}

int pfr_disk_write(int fd, const void *source_struct, int source_size, const void *flex_value, int flex_size, const char *err_id)
{
    int write_size_a = 0, write_size_b = 0;
     
    write_size_a = write(fd, source_struct, source_size);
    
    if (write_size_a == -1)
        fprintf(stderr, "Error writing %s structure data: %s\n", err_id, strerror(errno));
    
    if (write_size_a != source_size)
        return 0;
    
    write_size_b = write(fd, flex_value, flex_size);
    
    if (write_size_b == -1)
        fprintf(stderr, "Error writing %s flexible value: %s\n", err_id, strerror(errno));
    
    if (write_size_b != flex_size)
        return 0;
    
    return 1;
}

#endif
