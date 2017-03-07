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

struct pfr_detail {
    int type_id;
    int profile_id;
    int detail_id;
    int bsize;
};

int pfr_detail_save(struct pfr_detail *detail, const void *value);
int pfr_detail_delete(struct pfr_detail);

static int pfr_detail_read(FILE *, struct pfr_detail *target, void **value);
static int pfr_detail_write(FILE *, struct pfr_detail source, void *value);

static int profile_match(struct pfr_detail a, struct pfr_detail b);
