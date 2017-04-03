#include <stdlib.h>
#include <assert.h>
#include <pfr_files.h>

void init_all_files()
{
    assert(_get_home_dir() != NULL);
}

void _init_file(const char *filename)
{
    
}

const char *get_detail_file()
{
    return NULL;
}

const char *get_type_file()
{
    return NULL;
}

const char *get_tmp_detail_file()
{
    return NULL;
}

const char *get_tmp_type_file()
{
    return NULL;
}

const char *_get_home_dir()
{
#ifdef _WIN32
    return getenv("APPDATA");
#elif defined _linux_
    return getenv("HOME");
#else
#error Platform not s
#endif
    return NULL;
}
