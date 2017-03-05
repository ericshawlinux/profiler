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

#ifndef PFR_PERSON_FILTER_DEFINED
#define PFR_PERSON_FILTER_DEFINED

#include "pfr_filter.h"
#include "pfr_list.c"
#include "pfr_config.h"

#include <stdio.h>


// The following modes affect both type and detail filtering

#define FILTER_MODE_TYPE_ID_EQUALS          0x001
#define FILTER_MODE_TYPE_ID_LESS_THAN       0x002
#define FILTER_MODE_TYPE_ID_GRTR_THAN       0x004
#define FILTER_MODE_TYPE_ID_LTE            (0x001 | 0x002)
#define FILTER_MODE_TYPE_ID_GTE            (0x001 | 0x004)

#define FILTER_MODE_DATA_TYPE_EQUALS        0x010

#define FILTER_MODE_TYPE_NAME_EQUALS        0x020
#define FILTER_MODE_TYPE_NAME_CONTAINS      0x040
#define FILTER_MODE_TYPE_NAME_STARTS_WITH   0x080

// The following modes only affect detail filtering

#define FILTER_MODE_PROFILE_ID_EQUALS       0x0000100
#define FILTER_MODE_PROFILE_ID_LESS_THAN    0x0000200
#define FILTER_MODE_PROFILE_ID_GRTR_THAN    0x0000400
#define FILTER_MODE_PROFILE_ID_LTE         (0x0000100 | 0x0000200)
#define FILTER_MODE_PROFILE_ID_GTE         (0x0000100 | 0x0000400)

#define FILTER_MODE_DETAIL_ID_EQUALS        0x0001000
#define FILTER_MODE_DETAIL_ID_LESS_THAN     0x0002000
#define FILTER_MODE_DETAIL_ID_GRTR_THAN     0x0004000
#define FILTER_MODE_DETAIL_ID_LTE          (0x0001000 | 0x0002000)
#define FILTER_MODE_DETAIL_ID_GTE          (0x0001000 | 0x0004000)

#define FILTER_MODE_NUMBER_EQUALS           0x0010000
#define FILTER_MODE_NUMBER_LESS_THAN        0x0020000
#define FILTER_MODE_NUMBER_GRTR_THAN        0x0040000
#define FILTER_MODE_NUMBER_LTE             (0x0010000 | 0x0020000)
#define FILTER_MODE_NUMBER_GTE             (0x0010000 | 0x0040000)

#define FILTER_MODE_DATE_EQUALS             0x0100000
#define FILTER_MODE_DATE_LESS_THAN          0x0200000
#define FILTER_MODE_DATE_GRTR_THAN          0x0400000
#define FILTER_MODE_DATE_LTE               (0x0100000 | 0x0200000)
#define FILTER_MODE_DATE_GTE               (0x0100000 | 0x0400000)

#define FILTER_MODE_TEXT_EQUALS             0x1000000
#define FILTER_MODE_TEXT_CONTAINS           0x2000000
#define FILTER_MODE_TEXT_STARTS_WITH        0x4000000


#define TRUE 1
#define FALSE 0


list *pfr_type_filter(struct pfr_type *search, const char *type_name, int filter_mode)
{
    list *matching_types = NULL;
    struct pfr_type current = {0};
    char *current_name = NULL;
    FILE *type_fp = fopen(PFR_CFG_TYPE_FILE, "rb");
    
    if (type_fp == NULL)
        perror("Error in type filter");
    
    else while(pfr_type_read(type_fp, &current, &current_name)) {
        
        if (pfr_type_matches_filter(&current, current_name, search, type_name, filter_mode)) {
            // push (beginning) the matching type, then it's name.
            unshift_list(&current, sizeof current, &matching_types);
            unshift_list(current_name, strlen(current_name) + 1, &matching_types);
        }
    }
    
    fclose(type_fp);
    free(current_name);
    
    return matching_types;
}

list *pfr_detail_filter(struct pfr_type *type_search, const char *type_name,
                        struct pfr_detail *detail_search, void *detail_value, int filter_mode)
{
    list *matching_details = NULL;
    
    struct pfr_detail   current         = {0};
    void                *current_value  = NULL;
    struct pfr_type     current_type    = {0};
    char                *current_name   = NULL;
    
    FILE *detail_fp = fopen(PFR_CFG_DATA_FILE, "rb");
    
    if (detail_fp == NULL)
        perror("Error in detail filter");
    
    else while(pfr_detail_read(detail_fp, &current, &current_value)) {
        
        if (pfr_detail_matches_filter(&current, current_value, detail_search, detail_value, filter_mode)) {
            
            current_type = pfr_type_load(current.type_id, &current_name);
            
            if (pfr_type_matches_filter(&current_type, current_name, type_search, type_name, filter_mode)) {
                unshift_list(&current, sizeof current, &matching_details);
                unshift_list(current_value, current.bsize, &matching_details);
            }
        }
    }
    
    fclose(detail_fp);
    free(current_name);
    free(current_value);
    
    return matching_details;
}

static int pfr_type_matches_filter(struct pfr_type *a, const char *a_name,
                                   struct pfr_type *b, const char *b_name, int filter_mode)
{
    /** Type ID Filters ***************************************/
    
    if (filter_mode & FILTER_MODE_TYPE_ID_LTE && a->type_id > b->type_id)
        return FALSE;
        
    else if (filter_mode & FILTER_MODE_TYPE_ID_GTE && a->type_id < b->type_id)
        return FALSE;
    
    else if (filter_mode & FILTER_MODE_TYPE_ID_EQUALS && a->type_id != b->type_id)
        return FALSE;
        
    else if (filter_mode & FILTER_MODE_TYPE_ID_LESS_THAN && a->type_id >= b->type_id)
        return FALSE;
    
    else if (filter_mode & FILTER_MODE_TYPE_ID_GRTR_THAN && a->type_id <= b->type_id)
        return FALSE;
        
    /** Data Type Equals **************************************/
    
    if (filter_mode & FILTER_MODE_DATA_TYPE_EQUALS && a->data_type != b->data_type)
        return FALSE;
    
    /** Type Name Filters *************************************/
    
    if (filter_mode & FILTER_MODE_TYPE_NAME_STARTS_WITH && !str_starts_with(b_name, a_name))
        return FALSE;

    else if (filter_mode & FILTER_MODE_TYPE_NAME_CONTAINS && strstr(b_name, a_name) == NULL)
        return FALSE;

    else if (filter_mode & FILTER_MODE_TYPE_NAME_EQUALS && !strcmp(b_name, a_name))
        return FALSE;
    
    return TRUE;
}

static int pfr_detail_matches_filter(struct pfr_detail *a, void *a_value,
                                     struct pfr_detail *b, void *b_value, int filter_mode)
{
    return TRUE;
}


int str_starts_with(const char *str, const char *pre)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? FALSE : strncmp(pre, str, lenpre) == 0;
}

#endif
