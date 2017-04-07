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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef __linux__
#include <pwd.h>
#elif defined _WIN32
#include <windows.h>
#else
#error "Platform not supported"
#endif

#include <pfr_files.h>

/* Paths to data files, which need initialized. */
char    *detail_file_path       = NULL,
        *type_file_path         = NULL,
        *tmp_detail_file_path   = NULL,
        *tmp_type_file_path     = NULL;

/* Returns a path to the data directory if file_name is NULL.
 * Otherwise, returns a path to that file in the data directory. */
static char *get_file_path(char *file_name);

/* Concatenates two paths with an OS dependent separator. current should be in the heap */
static void concat_path(char **current, char *path);

/* Gets the user's personal directory. */
static const char *get_home_dir();

/* Initializes one file, given the filename. */
static int init_file(const char *file_path);

int init_all_files()
{
    // create the data directory
    char *data_dir = get_file_path(NULL);
#ifdef __linux__
	if (mkdir(data_dir, DATA_DIR_PERMISSIONS) == -1 && errno != EEXIST)
#elif defined _WIN32
	if (!CreateDirectory(data_dir, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
#else
#error "Platform not supported"
#endif
    {
        perror("Error creating data directory");
        return 0;
    }
    free(data_dir);
    
    // set globals, to use in rest of program
    detail_file_path        = get_file_path("details.dat");
    tmp_detail_file_path    = get_file_path("details.tmp");
    type_file_path          = get_file_path("types.dat");
    tmp_type_file_path      = get_file_path("types.tmp");
    
    // try to create the files
    if (!init_file(detail_file_path))
        return 0;
    if (!init_file(tmp_detail_file_path))
        return 0;
    if (!init_file(type_file_path))
        return 0;
    if (!init_file(tmp_type_file_path))
        return 0;
    
    return 1;
}

static int init_file(const char *file_path)
{
    if (file_path == NULL)
        return 0;
    FILE *fp = fopen(file_path, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Error initializing file: %s : %s\n", file_path, strerror(errno));
        return 0;
    }
    fclose(fp);
    return 1;
}

static char *get_file_path(char *file_name)
{
    const char *home_dir = get_home_dir();
    char *path = NULL;
    path = malloc(strlen(home_dir) + 1);
    if (path == NULL)
    {
        return NULL;
    }
    memset(path, 0, strlen(home_dir) + 1);
    strncpy(path, home_dir, strlen(home_dir));
    concat_path(&path, ".profiler");
    if (file_name == NULL)
    {
        return path;
    }
    concat_path(&path, file_name);
    return path;
}

static void concat_path(char **current, char *path)
{
    *current = realloc(*current, strlen(*current) + strlen(path) + PATH_SEPARATOR_LENGTH + 1);
    strcat(*current, PATH_SEPARATOR);
    strcat(*current, path);
}

static const char *get_home_dir()
{
#ifdef _WIN32
    return getenv("APPDATA");
#elif defined __linux__
    char *home_dir = getenv("HOME");
    if (home_dir == NULL)
        home_dir = getpwuid(getuid())->pw_dir;
    return home_dir;
#else
#error "Platform not supported"
#endif
}
