/*
 * Copyright 2017 Eric Shaw Jr <ericshaw.linux@gmail.com>
 * 
 * This file is part of profiler.
 * 
 * profiler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * profiler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with profiler.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef PFR_DISK_DEFINED
#define PFR_DISK_DEFINED

#include <malloc.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int pfr_disk_read(FILE *fp, void *target_struct, int target_size, void **flex_value, const int *flex_size, const char *err_id)
{
    int read_size_a = 0, read_size_b = 0;
    
    read_size_a = fread(target_struct, 1, target_size, fp);
    
    if (read_size_a != target_size) {
        fprintf(stderr, "Error reading %s structure data: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    *flex_value = realloc(*flex_value, *flex_size);
    
    if (*flex_value == NULL) {
        fprintf(stderr, "Error allocating memory for %s flexible value: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    read_size_b = fread(*flex_value, 1, *flex_size, fp);
    
    if (read_size_b != *flex_size) {
        fprintf(stderr, "Error reading %s flexible value: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    return 1;
}

int pfr_disk_write(FILE *fp, const void *source_struct, int source_size, const void *flex_value, int flex_size, const char *err_id)
{
    int write_size_a = 0, write_size_b = 0;
     
    write_size_a = fwrite(source_struct, 1, source_size, fp);
    
    if (write_size_a != source_size) {
        fprintf(stderr, "Error writing %s structure data: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    write_size_b = fwrite(flex_value, 1, flex_size, fp);

    if (write_size_b != flex_size) {
        fprintf(stderr, "Error writing %s flexible value: %s\n", err_id, strerror(errno));
        return 0;
    }
    
    return 1;
}

#endif
