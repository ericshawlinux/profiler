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

#ifndef PFR_DISK_DEFINED
#define PFR_DISK_DEFINED

int pfr_disk_read(FILE *fp, void *target_struct, int target_size, char **flex_value, int *flex_size, const char *err_id);
int pfr_disk_write(FILE *fp, const void *source_struct, int source_size, const char *flex_value, int flex_size, const char *err_id);

#endif // pfr_disk.h included
