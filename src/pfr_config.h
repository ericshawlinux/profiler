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

#ifndef PFR_CFG_DEFINED
#define PFR_CFC_DEFINED

    #ifdef __linux__

        #define PFR_CFG_DATA_FILE       "/home/eric/Projects/profiler/data/profiles.dat"
        #define PFR_CFG_DATA_TEMP_FILE  "/home/eric/Projects/profiler/data/profiles.tmp"
        #define PFR_CFG_TYPE_FILE       "/home/eric/Projects/profiler/data/types.dat"
        #define PFR_CFG_TYPE_TEMP_FILE  "/home/eric/Projects/profiler/data/types.tmp"

    #elif defined __MINGW32__

        #define PFR_CFG_DATA_FILE       "C:\\Dev\\profiler\\data\\profiles.dat"
        #define PFR_CFG_DATA_TEMP_FILE  "C:\\Dev\\profiler\\data\\profiles.tmp"
        #define PFR_CFG_TYPE_FILE       "C:\\Dev\\profiler\\data\\types.dat"
        #define PFR_CFG_TYPE_TEMP_FILE  "C:\\Dev\\profiler\\data\\types.tmp"
        
    #endif

    #define PFR_CFG_TYPE_FIRST_ID 1
    #define PFR_CFG_DETAIL_FIRST_ID 1
    #define PFR_CFG_PROFILE_FIRST_ID 1

#endif // pfr_config.h included
