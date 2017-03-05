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

#ifndef PFR_LIST_DEFINED
#define PFR_LIST_DEFINED

#include <pfr_list.h>

#include <malloc.h>
#include <string.h>

void unshift_list(void *bytes, int bsize, list **head)
{
    list *new;
    new = malloc(sizeof(int) + sizeof(struct node*) + bsize);
    
    new->bsize = bsize;
    memcpy(new->bytes, bytes, bsize);
    
    new->next = *head;
    *head = new;
}

void free_list(list *head)
{
    if (head != NULL && head->next != NULL)
        free_list(head->next);

    free(head);
}

#endif // pfr_list.c included
