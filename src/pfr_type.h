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

struct pfr_type {
    int   type_id;
    char  data_type;
    int   nsize;
};

struct pfr_type pfr_type_load(int in_type_id, char **out_type_name);
int pfr_type_save(struct pfr_type *, const char *name);
int pfr_type_delete(const char *type_name, int type_id);
void pfr_type_print();

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name);
static int pfr_type_read(FILE *fd, struct pfr_type *target, char **name);
static int pfr_type_write(FILE *fd, const struct pfr_type type, const char *name);
