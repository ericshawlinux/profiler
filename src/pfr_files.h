#ifndef PFR_FILES_DEFINED
#define PFR_FILES_DEFINED

/* Initializes all of the data files in the user's directory. */
void init_all_files();

/* Initializes one file, given the filename. */
void _init_file(const char *filename);

/* Gets the detail file for this user. */
const char *get_detail_file();

/* Gets the type file for this user. */
const char *get_type_file();

/* Temporary files used for copying. */
const char *get_tmp_detail_file();
const char *get_tmp_type_file();

/* Gets the user's personal directory. */
const char *_get_home_dir();

#endif
