#ifndef PFR_TYPE_DEFINED
#define PFR_TYPE_DEFINED

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "pfr_type.h"
#include "pfr_config.h"
#include "pfr_disk.c"

int pfr_type_save(struct pfr_type *type, const char *name)
{
    int name_exists = 0, next_id = PFR_CFG_TYPE_FIRST_ID;
    
    if (!pfr_type_get_state(&next_id, &name_exists, name))
        return 0;
    
    if (name_exists) {
        printf("Type %s already defined\n", name);
        return 0;
    }
    
    type->type_id = next_id;
    
    FILE *fp = fopen(PFR_CFG_TYPE_FILE, "ab");
    
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
    FILE *origin = fopen(PFR_CFG_TYPE_FILE, "rb");
    FILE *dest = fopen(PFR_CFG_TYPE_TEMP_FILE, "wb");

    if (origin == NULL || dest == NULL) {
        perror("Error opening type files");
        return 0;
    }

    struct pfr_type current_type;
    char *current_name = NULL;
    
    while (pfr_type_read(origin, &current_type, &current_name))
    {
        if (!strcmp(current_name, type_name) || current_type.type_id == type_id)
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

    remove(PFR_CFG_TYPE_FILE);
    rename(PFR_CFG_TYPE_TEMP_FILE, PFR_CFG_TYPE_FILE);
    
    free(current_name);
    
    return 1;
}

void pfr_type_print()
{
    FILE *fp = fopen(PFR_CFG_TYPE_FILE, "rb");

    if (fp == NULL) {
        perror("Error opening type file for reading");
        return;
    }

    struct pfr_type itype;
    char *iname = NULL;

    printf("type_id data_type type_name\n");

    while (pfr_type_read(fp, &itype, &iname))
        printf("%7d %9c %s\n", itype.type_id, itype.data_type, iname);
        
    free(iname);

    fclose(fp);
    return;
}

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name)
{
    FILE *fp = fopen(PFR_CFG_TYPE_FILE, "rb");

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

static int pfr_type_read(FILE *fp, struct pfr_type *target, char **name)
{
    return pfr_disk_read(fp, target, sizeof *target, (void **) name, &(target->nsize), "type");
}

static int pfr_type_write(FILE *fp, struct pfr_type source, const char *name)
{
    return pfr_disk_write(fp, &source, sizeof source, (void **) name, source.nsize, "type");
}

#endif // pfr_type included
