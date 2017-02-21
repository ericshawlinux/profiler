struct pfr_type {
    int   type_id;
    char  data_type;
    int   nsize;
};

int pfr_type_save(struct pfr_type *, const char *name);
int pfr_type_delete(const char *type_name, int type_id);
void pfr_type_print();

static int pfr_type_get_state(int *next_id, int *name_exists, const char *name);
static int pfr_type_read(int fd, struct pfr_type *target, char **name);
static int pfr_type_write(int fd, const struct pfr_type type, const char *name);
