#ifndef PFR_TYPE_DEFINED
#define PFR_TYPE_DEFINED

#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
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
    
    int fd = open(PFR_CFG_TYPE_FILE, O_WRONLY | O_APPEND);
    
    if (fd == -1) {
        perror("Error opening type file for saving");
        return 0;
    }
    
    if (!pfr_type_write(fd, *type, name)) {
        close(fd);
        return 0;
    }
    
    close(fd);
    return 1;
}

int pfr_type_delete(const char *type_name, int type_id)
{
    int origin = open(PFR_CFG_TYPE_FILE, O_RDONLY | O_CREAT, PFR_CFG_PERMITTED);
    int dest = open(PFR_CFG_TYPE_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, PFR_CFG_PERMITTED);

    if (origin == -1 || dest == -1) {
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
            close(origin);
            close(dest);
            return 0;
        }
    }

    close(origin);
    close(dest);

    remove(PFR_CFG_TYPE_FILE);
    rename(PFR_CFG_TYPE_FILE, PFR_CFG_TYPE_TEMP_FILE);
    
    free(current_name);
    
    return 1;
}

void pfr_type_print()
{
    int fd = open(PFR_CFG_TYPE_FILE, O_RDONLY | O_CREAT, PFR_CFG_PERMITTED);

    if (fd == -1) {
        perror("Error opening type file for reading");
        return;
    }

    struct pfr_type itype;
    char *iname = NULL;

    printf("type_id data_type type_name\n");

    while (pfr_type_read(fd, &itype, &iname))
        printf("%7d %9c %s\n", itype.type_id, itype.data_type, iname);
        
    free(iname);

    close(fd);
    return;
}

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name)
{
    int fd = open(PFR_CFG_TYPE_FILE, O_RDONLY | O_CREAT, PFR_CFG_PERMITTED);

    if (fd == -1) {
        perror("Error opening type file for reading");
        return 0;
    }

    struct pfr_type itype;
    char *iname = NULL;

    while (pfr_type_read(fd, &itype, &iname)) {
        
        *name_exists = *name_exists || !strcmp(iname, name);
        
        if (itype.type_id >= *next_id)
            *next_id = itype.type_id + 1; 
    }
    
    free(iname);

    close(fd);
    return 1;
}

static int pfr_type_read(int fd, struct pfr_type *target, char **name)
{
    return pfr_disk_read(fd, target, sizeof *target, (void **) name, &(target->nsize), "type");
}

static int pfr_type_write(int fd, struct pfr_type source, const char *name)
{
    return pfr_disk_write(fd, &source, sizeof source, (void **) name, source.nsize, "type");
}

#endif // pfr_type included
