#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pfr_type.c"

static void usage()
{
    printf("usage: ");
}

static void fatal(const char *msg)
{
    printf("fatal: %s\n", msg);
}

#define DATA_TYPE_SIZE 7

static void pfr_cmd_type_define(int argc, const char **argv)
{
    if (argc != 4)
        return;
    
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
        return;
    
    type.nsize = strlen(argv[2]) + 1;
    
    if (!pfr_type_save(&type, argv[2]))
        fatal("unable to define type");
}

static void pfr_cmd_type_undefine(int argc, const char **argv)
{
    if (argc < 3)
        return usage();
    
    char *type_name = NULL;
    int type_id = 0;
    
    int i;
    for (i = 2; i < argc; i++) {
        
        if (type_name == NULL && *argv[i] != '-') {
            int argl = strlen(argv[i]) + 1;
            type_name = malloc(argl);
            strncpy(type_name, argv[i], argl);
        }
        
        else if (type_id < 1 && !strcmp(argv[i], "--type-id")) {
        
            if (i+1 >= argc)
                return fatal("no type id specified");
        
            type_id = strtol(argv[++i], NULL, 10);
        
            if (type_id < PFR_CFG_TYPE_FIRST_ID)
                return fatal("invalid type id number");
        }
        
        else
            return fatal("unrecognized option");
    }
    
    // TODO: warn if details of this type exist and exit
    
    if (!pfr_type_delete(type_name, type_id))
        fatal("unable to delete type");
    
    free(type_name);
}

static void pfr_cmd_type_show()
{
    pfr_type_print();
}

static void pfr_cmd_detail_set()
{

}

static void pfr_cmd_detail_get()
{

}

static void pfr_cmd_help()
{

}

struct cmd_struct {
    const char *cmd;
    void (*fn)(int argc, const char **argv);
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

#define noop do {} while(0)

int main(int argc, const char **argv)
{
    struct cmd_struct *cmd = NULL;
    
    if (argc >= 2)
        cmd = get_builtin(argv[1]);
    
    if (cmd == NULL)
        usage();
        
    else
        cmd->fn(argc, argv);
    
    return 0;
}
