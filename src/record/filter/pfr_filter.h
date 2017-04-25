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


#ifndef PFR_FILTER_DEFINED
#define PFR_FILTER_DEFINED

#include "pfr_list.h"
#include "pfr_type.h"
#include "pfr_detail.h"


// The following modes affect both type and detail filtering

#define FILTER_MODE_TYPE_ID_EQUALS          0x001
#define FILTER_MODE_TYPE_ID_LESS_THAN       0x002
#define FILTER_MODE_TYPE_ID_GRTR_THAN       0x004

#define FILTER_MODE_DATA_TYPE_EQUALS        0x010

#define FILTER_MODE_TYPE_NAME_EQUALS        0x020
#define FILTER_MODE_TYPE_NAME_CONTAINS      0x040
#define FILTER_MODE_TYPE_NAME_STARTS_WITH   0x080

// The following modes only affect detail filtering

#define FILTER_MODE_PROFILE_ID_EQUALS       0x000100
#define FILTER_MODE_PROFILE_ID_LESS_THAN    0x000200
#define FILTER_MODE_PROFILE_ID_GRTR_THAN    0x000400

#define FILTER_MODE_DETAIL_ID_EQUALS        0x001000
#define FILTER_MODE_DETAIL_ID_LESS_THAN     0x002000
#define FILTER_MODE_DETAIL_ID_GRTR_THAN     0x004000

#define FILTER_MODE_NUMBER_EQUALS           0x010000
#define FILTER_MODE_NUMBER_LESS_THAN        0x020000
#define FILTER_MODE_NUMBER_GRTR_THAN        0x040000

#define FILTER_MODE_TEXT_EQUALS             0x100000
#define FILTER_MODE_TEXT_CONTAINS           0x200000
#define FILTER_MODE_TEXT_STARTS_WITH        0x400000

/* used to determine the current filter, order of usage still matters.
 * first, use FILTER_MODE_COMPOUND_MATCH for lte, gte.
 * then, use FILTER_MODE_MATCH. */
 
#define FILTER_MODE_MATCH(mode, target) (mode & target)
#define FILTER_MODE_COMPOUND_MATCH(mode, A, B) FILTER_MODE_MATCH(mode, A) && FILTER_MODE_MATCH(mode, B)

#define TRUE 1
#define FALSE 0


list *pfr_type_filter(
    struct pfr_type     search,
    const char          *type_name,
    int                 filter_mode
);

list *pfr_detail_filter(
    struct pfr_type     type_search,
    const char          *type_name,
    struct pfr_detail   detail_search,
    void                *value,
    int                 filter_mode
);

// use for searching text types
int str_starts_with(const char *str, const char *pre);

#endif // pfr_filter.h included
