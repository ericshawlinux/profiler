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

#ifndef PFR_DETAIL_DEFINED
#define PFR_DETAIL_DEFINED

#include <stdio.h>

struct pfr_detail {
    int type_id;
    int profile_id;
    int detail_id;
    int bsize;
};

int pfr_detail_get_next_profile_id();
int pfr_detail_get_next_detail_id(int profile_id);

int pfr_detail_save(struct pfr_detail *detail, const char *value);
int pfr_detail_delete(struct pfr_detail);

int pfr_detail_read(FILE *, struct pfr_detail *target, char **value);

#endif // pfr_detail.h included
