struct pfr_detail {
    int type_id;
    int profile_id;
    int detail_id;
    int bsize;
};

int pfr_detail_save(struct pfr_detail *detail, const void *value);
int pfr_detail_delete(struct pfr_detail);

static int pfr_detail_get_state(struct pfr_detail *detail);
static int pfr_detail_read(int fd, struct pfr_detail *target, void **value);
static int pfr_detail_write(int fd, struct pfr_detail source, void *value);

static int profile_match(struct pfr_detail a, struct pfr_detail b);
