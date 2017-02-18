#include <stdio.h>
#include <string.h>

int pfr_cmd_type_define(int argc, const char **argv)
{
    return 0;
}

int pfr_cmd_type_undefine(int argc, const char **argv)
{
    return 0;
}

int pfr_cmd_type_show(int argc, const char **argv)
{
    return 0;
}

int pfr_cmd_detail_set(int argc, const char **argv)
{
    return 0;
}

int pfr_cmd_detail_get(int argc, const char **argv)
{
    return 0;
}

int pfr_cmd_help(int argc, const char **argv)
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

void usage(int argc, const char **argv, struct cmd_struct *cmd)
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
