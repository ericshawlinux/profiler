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

#ifndef PFR_USAGE
#define PFR_USAGE

#include <stdio.h>
#include <malloc.h>
#include <string.h>

static const char *usage_string =
    "usage: %s <command> [<args>]\n\n"
    "type commands:\n"
    "   def     Define a type of profile detail\n"
    "   undef   Remove a type if unused\n"
    "   show    Show all currently defined types\n\n"
    "detail commands:\n"
    "   new     Create a new detail (use --profile-id to add a new detail to an existing profile)\n"
    "   update  Update or delete a profile detail\n"
    "   get     Show profile details matching criteria\n\n"
    "See '%s help <command>' or 'profiler help <concept>' to read about a specific subcommand or concept.\n"
;

void usage(const char *program_name)
{
    char *usage_complete = malloc(strlen(usage_string) + strlen(program_name) * 2);
    
    if (usage_complete == NULL)
        return;
    
    sprintf(usage_complete, usage_string, program_name, program_name);
    printf("%s", usage_complete);
    
    free(usage_complete);
}

static const char *def_usage_string =
    "usage: %s def <type-name> <type>\n"
    "types: text, date, number\n"
;

void def_usage(const char *program_name)
{
    char *usage_complete = malloc(strlen(def_usage_string) + strlen(program_name));
    
    if (usage_complete == NULL)
        return;
    
    sprintf(usage_complete, def_usage_string, program_name);
    printf("%s", usage_complete);
    
    free(usage_complete);
}

static const char *undef_usage_string =
    "usage: %s undef <type-name | --type-id type-id>\n"
;

void undef_usage(const char *program_name)
{
    char *usage_complete = malloc(strlen(undef_usage_string) + strlen(program_name));
    
    if (usage_complete == NULL)
        return;
    
    sprintf(usage_complete, undef_usage_string, program_name);
    printf("%s", usage_complete);
    
    free(usage_complete);
}

static const char *new_usage_string =
    "usage: %s new <options> <value>\n"
    "\n"
    "options:\n"
    "   [--profile-id profile-id]\n"
    "   <type-name | --type-id type-id>\n"
    "\n"
;

void new_usage(const char *program_name)
{
    char *usage_complete = malloc(strlen(new_usage_string) + strlen(program_name));
    
    if (usage_complete == NULL)
        return;
    
    sprintf(usage_complete, new_usage_string, program_name);
    printf("%s", usage_complete);
    
    free(usage_complete);
}

#endif
