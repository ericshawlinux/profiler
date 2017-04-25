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

#include "pfr_list.h"

#include <malloc.h>
#include <string.h>

void prepend_list(
    list                **head,
    int                 has_type,
    int                 has_detail,
    struct pfr_type     type,
    char                *type_name,
    struct pfr_detail   detail,
    char                *detail_value
)
{
    list *new = malloc(sizeof (struct node));
    
    new->has_type       = has_type;
    new->has_detail     = has_detail;
    new->type           = type;
    new->detail         = detail;
    
    if (type_name != NULL) {
        new->type_name = malloc(new->type.nsize);
        strncpy(new->type_name, type_name, new->type.nsize);
    }
    
    if (detail_value != NULL) {
        new->detail_value = malloc(new->detail.bsize);
        memcpy(new->detail_value, detail_value, new->detail.bsize);
    }
    
    new->next = *head;
    *head = new;
}

void free_list(list *head)
{
    if (head != NULL && head->next != NULL) {
        free_list(head->next);
    }

    if (head != NULL) {
        if (head->has_type)
            free(head->type_name);
        if (head->has_detail)
            free(head->detail_value);
        free(head);
    }
}

int list_size(list *head)
{
    struct node *current = head;
    int count = 0;
    
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    
    return count;
}
