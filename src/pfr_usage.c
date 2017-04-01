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
#include <malloc.h>
#include <string.h>

const char *usage_string =
    "usage: %s <command> [<args>]\n\n"
    "type commands:\n"
    "   def     Define a type of profile detail\n"
    "   undef   Remove a type if unused\n"
    "   show    Show all currently defined types\n\n"
    "detail commands:\n"
    "   new     Create a new detail (use --profile-id to add a new detail to an existing profile)\n"
    "   update  Update or delete a profile detail\n"
    "   get     Show profile details matching criteria\n\n"
    "See '%s help <command>' or 'profiler help <concept>' to read about a specific subcommand or concept.\n";

const char *def_usage_string =
    "usage: %s def <type-name> <type>\n"
    "types: text, date, number\n";

const char *undef_usage_string =
    "usage: %s undef <type-name | --type-id type-id>\n";

const char *new_usage_string =
    "usage: %s new <options> <value>\n"
    "\n"
    "options:\n"
    "   [--profile-id profile-id]\n"
    "   <type-name | --type-id type-id>\n";

void usage_fmt_s(const char *fmt, const char *arg1)
{
    char *usage_complete = malloc(strlen(fmt) + strlen(arg1) + 1);
    if (usage_complete == NULL)
        return;
    sprintf(usage_complete, fmt, arg1);
    puts(usage_complete);
    free(usage_complete);
}

void usage_fmt_ss(const char *fmt, const char *arg1, const char *arg2)
{
    char *usage_complete = malloc(strlen(fmt) + strlen(arg1) + strlen(arg2) + 1);
    if (usage_complete == NULL)
        return;
    sprintf(usage_complete, usage_string, arg1, arg2);
    puts(usage_complete);
    free(usage_complete);
}
