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

#include <pfr_type.h>
#include <pfr_detail.h>

struct node {
    int                 has_type    :1;
    int                 has_detail  :1;
    struct pfr_type     type;
    char                *type_name;
    struct pfr_detail   detail;
    void                *detail_value;
    struct node         *next;
};

typedef struct node list;

void prepend_list(
    list                **head,
    int                 has_type,
    int                 has_detail,
    struct pfr_type     type,
    char                *type_name,
    struct pfr_detail   detail,
    void                *detail_value
);

void free_list(list *head);
int list_size(list *head);

#endif // pfr_list.h included
