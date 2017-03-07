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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pfr_type.c"
#include "pfr_usage.c"

#define DATA_TYPE_SIZE 7

// attempts to get an id number from argv[i]
static int arg_id(int argc, const char **argv, int i, unsigned int min, const char *desc)
{
    unsigned int id_number;
    
    if (i >= argc) {
        printf("error: no %s id specified\n", desc);
        return -1;
    }

    id_number = strtol(argv[i], NULL, 10);

    if (id_number < min) {
        printf("error: invalid %s id number\n", desc);
        return -1;
    }
    
    return id_number;
}

// attempts to allocate and set the value of argv[i] for later use
static int arg_aquire(int argc, const char **argv, int i, void **target)
{
    if (i >= argc) {
        printf("Error: not enough arguments\n");
        return 0;
    }
    
    int argl = strlen(argv[i]) + 1;
    *target = malloc(argl);
    
    if (*target == NULL) {
        perror("Error allocating memory");
        return 0;
    }
    
    strncpy(*target, argv[i], argl);
    
    return 1;
}

static void pfr_cmd_type_define(int argc, const char **argv)
{
    if (argc != 4) {
        def_usage(argv[0]);
        return;
    }
    
    char data_type[DATA_TYPE_SIZE];
    strncpy(data_type, argv[3], DATA_TYPE_SIZE);
    
    struct pfr_type type = {0};
    
    if (!strcmp(data_type, "text"))
        type.data_type = 't';
        
    else if (!strcmp(data_type, "date"))
        type.data_type = 'd';
        
    else if (!strcmp(data_type, "number"))
        type.data_type = 'n';
        
    else
    {
        printf("error: invalid type '%s'\n", data_type);
        def_usage(argv[0]);
        return;
    }
    
    type.nsize = strlen(argv[2]) + 1;
    
    if (!pfr_type_save(&type, argv[2]))
        printf("error: unable to define type\n");
}

static void pfr_cmd_type_undefine(int argc, const char **argv)
{
    if (argc < 3) {
        undef_usage(argv[0]);
        return;
    }
    
    char *type_name = NULL;
    int type_id = 0;
    
    int i;
    for (i = 2; i < argc; i++)
    {
        if (type_name == NULL && *argv[i] != '-')
        {
            if (!arg_aquire(argc, argv, i, (void **) &type_name))
                return;
        }
        
        else if (type_id < 1 && !strcmp(argv[i], "--type-id"))
        {
            type_id = arg_id(argc, argv, ++i, PFR_CFG_TYPE_FIRST_ID, "type");
            
            if (type_id == -1)
                return;
        }
        
        else
        {
            printf("error: unrecognized option '%s'\n", argv[i]);
            return;
        }
    }
    
    // TODO: warn if details of this type exist and exit
    
    if (!pfr_type_delete(type_name, type_id))
        printf("error: unable to delete type\n");
    
    free(type_name);
}

static void pfr_cmd_type_show(int argc, const char **argv)
{
    int     filter_mode         = 0;
    int     type_id_filter      = 0;
    char    data_type_filter    = 0;
    char    *type_name_filter   = NULL;
    list    *search_results     = NULL;
    
    int i;
    for (i = 2; i < argc; i++)
    {
        if (type_id_filter == 0 && str_starts_with(argv[i], "--type-id"))
        {
            if (!strcmp(argv[i], "--type-id-lte"))
                filter_mode |= FILTER_MODE_TYPE_ID_LTE;
            
            else if (!strcmp(argv[i], "--type-id-gte"))
                filter_mode |= FILTER_MODE_TYPE_ID_GTE;
            
            else if (!strcmp(argv[i], "--type-id-lt"))
                filter_mode |= FILTER_MODE_TYPE_ID_LESS_THAN;
            
            else if (!strcmp(argv[i], "--type-id-gt"))
                filter_mode |= FILTER_MODE_TYPE_ID_GRTR_THAN;
            
            else if (!strcmp(argv[i], "--type-id"))
                filter_mode |= FILTER_MODE_TYPE_ID_EQUALS;
            else {
                printf("unrecognized option %s\n", argv[i]);
                return;
            }
            
            // try to get the type-id value
            type_id_filter = arg_id(argc, argv, ++i, PFR_CFG_TYPE_FIRST_ID, "type");
            if (type_id_filter == -1)
                return;
        }
        else if (data_type_filter == 0 && str_starts_with(argv[i], "--data-type"))
        {
            i++;
            
            if (!strcmp("date", argv[i]))
                data_type_filter = 'd';
                
            else if (!strcmp("number", argv[i]))
                data_type_filter = 'n';
                
            else if (!strcmp("text", argv[i]))
                data_type_filter = 't';
            
            else {
                printf("unrecognized data-type filter %s\n", argv[i]);
                return;
            }
            
            filter_mode |= FILTER_MODE_DATA_TYPE_EQUALS;
        }
        else if (type_name_filter == NULL && str_starts_with(argv[i], "--type-name"))
        {
            if (!strcmp(argv[i], "--type-name")) {
                filter_mode |= FILTER_MODE_TYPE_NAME_EQUALS;
            }
            else if (!strcmp(argv[i], "--type-name-contains")) {
                filter_mode |= FILTER_MODE_TYPE_NAME_CONTAINS;
            }
            else if (!strcmp(argv[i], "--type-name-starts-with")) {
                filter_mode |= FILTER_MODE_TYPE_NAME_STARTS_WITH;
            }
            else {
                printf("unrecognized type-name filter: %s\n", argv[i]);
                return;
            }
            
            if (!arg_aquire(argc, argv, ++i, (void**) &type_name_filter))
                return;
        }
    }
    
    struct pfr_type search = {
        .type_id = type_id_filter,
        .data_type = data_type_filter,
    };
    
    search_results = pfr_type_filter(&search, type_name_filter, filter_mode);
    struct node *current = search_results;
    
    while (current != NULL)
    {
        pfr_type_print(current->type, current->type_name, current == search_results);
        current = current->next;
    }
    
    free(type_name_filter);
    free_list(search_results);
}

static void pfr_cmd_detail_new(int argc, const char **argv)
{
    if (argc < 4) {
        new_usage(argv[0]);
        return;
    }
    
    int profile_id = 0, type_id = 0;
    char *type_name = NULL;
    signed char *value = NULL;
    
    int i;
    for (i = 0; i < argc; i++)
    {
        if (profile_id > 0 && !strcmp(argv[i], "--profile-id"))
        {
            profile_id = arg_id(argc, argv, ++i, PFR_CFG_PROFILE_FIRST_ID, "profile");
            
            if (profile_id == -1)
                return;
        }
        
        else if (type_id > 0 && !strcmp(argv[i], "--type-id"))
        {
            type_id = arg_id(argc, argv, ++i, PFR_CFG_TYPE_FIRST_ID, "type");
            
            if (type_id == -1)
                return;
        }
        
        else if (*argv[i] == '-')
        {
            printf("error: unrecognized option %s", argv[i]);
            return;
        }
        
        else if (type_id == 0 && type_name == NULL)
        {
            if (!arg_aquire(argc, argv, i, (void **) &type_name))
                return;
        }
        
        else if (value == NULL)
        {
            if (!arg_aquire(argc, argv, i, (void **) &value))
                return;
        }
        
        else
        {
            printf("error: too many arguments\n");
            return;
        }
    }
    
    // get the type for the id number, and for converting value
    // to something useful like time_t, or int.
    // finally, set detail information and save.
    
    free(type_name);
    free(value);
}

static void pfr_cmd_detail_update()
{
    
}

static void pfr_cmd_detail_get()
{

}

static void pfr_cmd_help(int argc, const char **argv)
{
    usage(argv[0]);
}

struct cmd_struct {
    const char *cmd;
    void (*fn)(int argc, const char **argv);
};

static struct cmd_struct commands[] = {
    {"def",         pfr_cmd_type_define},
    {"undef",       pfr_cmd_type_undefine},
    {"show",        pfr_cmd_type_show},
    {"new",         pfr_cmd_detail_new},
    {"update",      pfr_cmd_detail_update},
    {"get",         pfr_cmd_detail_get},
    {"help",        pfr_cmd_help},
    {"define",      pfr_cmd_type_define},
    {"undefine",    pfr_cmd_type_undefine},
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static struct cmd_struct *get_builtin(const char *s)
{
    unsigned int i;
    for(i = 0; i < ARRAY_SIZE(commands); i++) {
        struct cmd_struct *p = commands + i;
        if (!strcmp(s, p->cmd))
            return p;
    }
    return NULL;
}

int main(int argc, const char **argv)
{
    struct cmd_struct *cmd = NULL;
    
    if (argc >= 2)
        cmd = get_builtin(argv[1]);
    
    if (cmd == NULL)
        usage(argv[0]);
        
    else
        cmd->fn(argc, argv);
    
    return 0;
}
