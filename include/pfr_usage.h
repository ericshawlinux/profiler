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

#ifndef PFR_USAGE_DEFINED
#define PFR_USAGE_DEFINED

const char *usage_string;
const char *def_usage_string;
const char *undef_usage_string;
const char *new_usage_string;

void usage_fmt_s(const char *fmt, const char *arg1);
void usage_fmt_ss(const char *fmt, const char *arg1, const char *arg2);

#endif // pfr_usage.h included
