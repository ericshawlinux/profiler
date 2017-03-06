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

#include "pfr_list.c"
#include "pfr_type.c"
#include "pfr_detail.c"

list *pfr_type_filter(
    struct pfr_type     *search,
    const char          *type_name,
    int                 filter_mode
);

list *pfr_detail_filter(
    struct pfr_type     *type_search,
    const char          *type_name,
    struct pfr_detail   *detail_search,
    void                *value,
    int                 filter_mode
);

static int pfr_type_matches_filter(
    struct pfr_type     *a,
    const char          *a_name,
    struct pfr_type     *b,
    const char          *b_name,
    int                 filter_mode
);

static int pfr_detail_matches_filter(
    struct pfr_detail   *a,
    void                *a_value,
    struct pfr_detail   *b,
    void                *b_value,
    int                 filter_mode
);

// use for searching text types
static int str_starts_with(const char *str, const char *pre);

