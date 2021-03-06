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

#include "pfr_type.h"
#include "pfr_files.h"
#include "pfr_disk.h"

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name);
static int pfr_type_write(FILE *fd, const struct pfr_type type, const char *name);

int pfr_type_save(struct pfr_type *type, const char *name)
{
    int name_exists = 0, next_id = 1;
    
    if (!pfr_type_get_state(&next_id, &name_exists, name))
        return 0;
    
    if (name_exists) {
        printf("Type %s already defined\n", name);
        return 0;
    }
    
    type->type_id = next_id;
    
    FILE *fp = fopen(type_file_path, "ab");
    
    if (fp == NULL) {
        perror("Error opening type file for saving");
        return 0;
    }
    
    if (!pfr_type_write(fp, *type, name)) {
        fclose(fp);
        return 0;
    }
    
    fclose(fp);
    return 1;
}

int pfr_type_delete(const char *type_name, int type_id)
{
    FILE *origin = fopen(type_file_path, "rb");
    FILE *dest = fopen(tmp_type_file_path, "wb");

    if (origin == NULL || dest == NULL) {
        perror("Error opening type files");
        return 0;
    }

    struct pfr_type current_type;
    char *current_name = NULL;
    
    while (pfr_type_read(origin, &current_type, &current_name))
    {
        if (current_type.type_id == type_id)
            continue;
        
        if (type_name != NULL && !strcmp(current_name, type_name))
            continue;
        
        if (!pfr_type_write(dest, current_type, current_name)) {
            free(current_name);
            fclose(origin);
            fclose(dest);
            return 0;
        }
    }

    fclose(origin);
    fclose(dest);

    remove(type_file_path);
    rename(tmp_type_file_path, type_file_path);
    
    free(current_name);
    
    return 1;
}

void pfr_type_print(struct pfr_type type, const char *type_name, int print_header)
{
    if (print_header)
        printf("type_id data_type type_name\n");
    
    printf("%7d %9c %s\n", type.type_id, type.data_type, type_name);
}

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name)
{
    FILE *fp = fopen(type_file_path, "rb");

    if (fp == NULL) {
        perror("Error opening type file for reading");
        return 0;
    }

    struct pfr_type itype;
    char *iname = NULL;

    while (pfr_type_read(fp, &itype, &iname)) {
        
        *name_exists = *name_exists || !strcmp(iname, name);
        
        if (itype.type_id >= *next_id)
            *next_id = itype.type_id + 1; 
    }
    
    free(iname);

    fclose(fp);
    return 1;
}

int pfr_type_read(FILE *fp, struct pfr_type *target, char **name)
{
    return pfr_disk_read(fp, target, sizeof *target, name, &(target->nsize), "type");
}

static int pfr_type_write(FILE *fp, struct pfr_type source, const char *name)
{
    return pfr_disk_write(fp, &source, sizeof source, name, source.nsize, "type");
}
