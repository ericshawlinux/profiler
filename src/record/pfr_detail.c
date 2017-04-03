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

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include <pfr_detail.h>
#include <pfr_files.h>
#include <pfr_disk.h>

static int pfr_detail_write(FILE *, struct pfr_detail source, void *value);
static int profile_match(struct pfr_detail a, struct pfr_detail b);

int pfr_detail_save(struct pfr_detail *detail, const void *value)
{
    FILE *fp = fopen(get_detail_file(), "ab");
    
    if (fp == NULL) {
        perror("Error opening detail file for saving");
        return 0;
    }
    
    if (!pfr_detail_write(fp, *detail, &value)) {
        fclose(fp);
        return 0;
    }
    
    fclose(fp);
    return 1;
}

int pfr_detail_delete(struct pfr_detail detail)
{
    FILE *origin = fopen(get_detail_file(), "rb");
    FILE *dest = fopen(get_tmp_detail_file(), "wb");

    if (origin == NULL || dest == NULL) {
        perror("Error opening type files");
        return 0;
    }

    struct pfr_detail current_detail;
    void *current_value = NULL;
    
    while (pfr_detail_read(origin, &current_detail, &current_value))
    {
        if (profile_match(current_detail, detail) && current_detail.detail_id == detail.detail_id)
            continue;
        
        if (!pfr_detail_write(dest, current_detail, current_value)) {
            free(current_value);
            fclose(origin);
            fclose(dest);
            return 0;
        }
    }

    fclose(origin);
    fclose(dest);

    remove(get_detail_file());
    rename(get_tmp_detail_file(), get_detail_file());
    
    free(current_value);
    
    return 1;
}

int pfr_detail_read(FILE *fp, struct pfr_detail *target, void **value)
{
    return pfr_disk_read(fp, target, sizeof *target, value, &(target->bsize), "detail");
}

static int pfr_detail_write(FILE *fp, struct pfr_detail source, void *value)
{
    return pfr_disk_write(fp, &source, sizeof source, value, source.bsize, "detail");
}

static int profile_match(struct pfr_detail a, struct pfr_detail b)
{
    if (a.type_id != b.type_id)
        return 0;
    
    if (a.profile_id != b.profile_id)
        return 0;
    
    return 1;
}
