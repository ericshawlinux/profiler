#ifndef PFR_DETAIL_DEFINED
#define PFR_DETAIL_DEFINED

#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#ifdef __linux__
#include <unistd.h>
#endif

#include "pfr_detail.h"
#include "pfr_config.h"
#include "pfr_disk.c"

int pfr_detail_save(struct pfr_detail *detail, const void *value)
{
    if (!pfr_detail_get_state(detail))
        return 0;
    
    int fd = open(PFR_CFG_DATA_FILE, O_WRONLY | O_APPEND);
    
    if (fd == -1) {
        perror("Error opening detail file for saving");
        return 0;
    }
    
    if (!pfr_detail_write(fd, *detail, &value)) {
        close(fd);
        return 0;
    }
    
    close(fd);
    return 1;
}

int pfr_detail_delete(struct pfr_detail detail)
{
	int origin = open(PFR_CFG_DATA_FILE, O_RDONLY | O_CREAT, PFR_CFG_PERMITTED);
    int dest = open(PFR_CFG_DATA_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, PFR_CFG_PERMITTED);

    if (origin == -1 || dest == -1) {
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
            close(origin);
            close(dest);
            return 0;
        }
    }

    close(origin);
    close(dest);

    remove(PFR_CFG_DATA_FILE);
    rename(PFR_CFG_DATA_FILE, PFR_CFG_DATA_TEMP_FILE);
    
    free(current_value);
    
    return 1;
}

int pfr_detail_get_state(struct pfr_detail *detail)
{
    int fd = open(PFR_CFG_DATA_FILE, O_RDONLY | O_CREAT, PFR_CFG_PERMITTED);

    if (fd == -1) {
        perror("Error opening data file for reading");
        return 0;
    }

    struct pfr_detail current_detail;
    void *current_value = NULL;
    
    detail->detail_id = PFR_CFG_DETAIL_FIRST_ID;

    while (pfr_detail_read(fd, &current_detail, &current_value)) {
        
        if (!profile_match(current_detail, *detail))
            continue;
        
        if (current_detail.detail_id >= detail->detail_id)
            detail->detail_id = current_detail.detail_id + 1; 
    }
    
    free(current_value);

    close(fd);
    return 1;
}

int pfr_detail_read(int fd, struct pfr_detail *target, void **value)
{
    return pfr_disk_read(fd, target, sizeof(struct pfr_detail), value, target->bsize, "detail");
}

int pfr_detail_write(int fd, struct pfr_detail source, void *value)
{
    return pfr_disk_write(fd, &source, sizeof(source), value, source.bsize, "detail");
}

int profile_match(struct pfr_detail a, struct pfr_detail b)
{
    if (a.type_id != b.type_id)
        return 0;
    
    if (a.profile_id != b.profile_id)
        return 0;
    
    return 1;
}

#endif // pfr_detail included
