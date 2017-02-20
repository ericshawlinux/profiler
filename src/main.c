#include <stdio.h>
#include <string.h>

#include "pfr_type.c"

#define DATA_TYPE_SIZE 7

static int pfr_cmd_type_define(int argc, const char **argv)
{
    if (argc != 4)
        return 0;
    
    char data_type[DATA_TYPE_SIZE];
    strncpy(data_type, argv[3], DATA_TYPE_SIZE);
    
    struct pfr_type type = {0};
    
    if (!strcmp(data_type, "text"))
        type.data_type = 't';
        
    else if (!strcmp(data_type, "date"))
        type.data_type = 'd';
        
    else if (!strcmp(data_type, "number"))
        type.data_type = 'n';
        
    else
        return 0;
    
    type.nsize = strlen(argv[2]) + 1;
    
    return pfr_type_save(&type, argv[2]);
}

static int pfr_cmd_type_undefine(int argc, const char **argv)
{
    if (argc != 3)
        return 0;
    
    return pfr_type_delete(argv[2], 0);
}

static int pfr_cmd_type_show(int argc, const char **argv)
{
    return 0;
}

static int pfr_cmd_detail_set(int argc, const char **argv)
{
    return 0;
}

static int pfr_cmd_detail_get(int argc, const char **argv)
{
    return 0;
}

static int pfr_cmd_help(int argc, const char **argv)
{
    return 0;
}

struct cmd_struct {
    const char *cmd;
    int (*fn)(int argc, const char **argv);
};

static struct cmd_struct commands[] = {
    {"def",    pfr_cmd_type_define},
    {"undef",  pfr_cmd_type_undefine},
    {"show",   pfr_cmd_type_show},
    {"set",    pfr_cmd_detail_set},
    {"get",    pfr_cmd_detail_get},
    {"help",   pfr_cmd_help}
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static struct cmd_struct *get_builtin(const char *s)
{
    unsigned int i;
    for(i = 0; i < ARRAY_SIZE(commands); i++) {
        struct cmd_struct *p = commands + i;
        if (!strcmp(s, p->cmd))
            return p;
    }
    return NULL;
}

static void usage(int argc, const char **argv, struct cmd_struct *cmd)
{
    printf("usage: %s\n", argv[0]);
}

int main(int argc, const char **argv)
{
    struct cmd_struct *cmd = NULL;
    
    if (argc >= 2)
        cmd = get_builtin(argv[1]);
    
    if (cmd == NULL || !cmd->fn(argc, argv))
        usage(argc, argv, cmd);
    
    return 0;
}
