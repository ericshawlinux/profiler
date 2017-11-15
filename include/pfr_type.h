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

#ifndef PFR_TYPE_DEFINED
#define PFR_TYPE_DEFINED

#include <stdio.h>

struct pfr_type {
    int   type_id;
    char  data_type;
    int   nsize;
};

struct pfr_type pfr_type_load(int in_type_id, char **out_type_name);
int pfr_type_save(struct pfr_type *, const char *name);
int pfr_type_delete(const char *type_name, int type_id);
void pfr_type_print();

int pfr_type_read(FILE *fd, struct pfr_type *target, char **name);

#endif // pfr_type.h included
