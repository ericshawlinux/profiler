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

#ifndef PFR_FILES_DEFINED
#define PFR_FILES_DEFINED

#include <sys/types.h>

/* Paths to data files, which need initialized. */
extern char *detail_file_path,
            *type_file_path,
            *tmp_detail_file_path,
            *tmp_type_file_path;

/* Initializes all of the data files in the user's directory. Returns true if it worked*/
int init_all_files();

/* Constants for OS dependent paths. */
#ifdef __linux__
#define PATH_SEPARATOR "/"
#define PATH_SEPARATOR_LENGTH 1
#elif defined _WIN32
#define PATH_SEPARATOR "\\"
#define PATH_SEPARATOR_LENGTH 2
#else
#error "Platform not supported"
#endif

#define DATA_DIR_PERMISSIONS S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH

#endif // pfr_files.h included
