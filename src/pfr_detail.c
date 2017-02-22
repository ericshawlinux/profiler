#ifndef PFR_DETAIL_DEFINED
#define PFR_DETAIL_DEFINED

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "pfr_detail.h"
#include "pfr_config.h"
#include "pfr_disk.c"

int pfr_detail_save(struct pfr_detail *detail, const void *value)
{
    if (!pfr_detail_get_state(detail))
        return 0;
    
    FILE *fp = fopen(PFR_CFG_DATA_FILE, "ab");
    
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
    FILE *origin = fopen(PFR_CFG_DATA_FILE, "rb");
    FILE *dest = fopen(PFR_CFG_DATA_TEMP_FILE, "wb");

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

    remove(PFR_CFG_DATA_FILE);
    rename(PFR_CFG_DATA_FILE, PFR_CFG_DATA_TEMP_FILE);
    
    free(current_value);
    
    return 1;
}

static int pfr_detail_get_state(struct pfr_detail *detail)
{
    FILE *fp = fopen(PFR_CFG_DATA_FILE, "rb");

    if (fp == NULL) {
        perror("Error opening data file for reading");
        return 0;
    }

    struct pfr_detail current_detail;
    void *current_value = NULL;
    
    detail->detail_id = PFR_CFG_DETAIL_FIRST_ID;

    while (pfr_detail_read(fp, &current_detail, &current_value)) {
        
        if (!profile_match(current_detail, *detail))
            continue;
        
        if (current_detail.detail_id >= detail->detail_id)
            detail->detail_id = current_detail.detail_id + 1; 
    }
    
    free(current_value);

    fclose(fp);
    return 1;
}

static int pfr_detail_read(FILE *fp, struct pfr_detail *target, void **value)
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

#endif // pfr_detail included
