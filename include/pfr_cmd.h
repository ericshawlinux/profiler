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

#ifndef PFR_CMD_DEFINED
#define PFR_CMD_DEFINED

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

struct cmd_struct {
    const char *cmd;
    void (*fn)(int argc, const char **argv);
};

struct cmd_struct *get_builtin(const char *s);

void pfr_cmd_type_define(int argc, const char **argv);
void pfr_cmd_type_undefine(int argc, const char **argv);
void pfr_cmd_type_show(int argc, const char **argv);
void pfr_cmd_detail_new(int argc, const char **argv);
void pfr_cmd_detail_update(int argc, const char **argv);
void pfr_cmd_detail_get(int argc, const char **argv);
void pfr_cmd_help(int argc, const char **argv);
void pfr_cmd_type_define(int argc, const char **argv);
void pfr_cmd_type_undefine(int argc, const char **argv);

#endif // pfr_cmd.h included
