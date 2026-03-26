#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct mini_unionfs_state {
    char lower_dir[PATH_MAX];
    char upper_dir[PATH_MAX];
};

#define UNIONFS_DATA ((struct mini_unionfs_state *) fuse_get_context()->private_data)

static void build_path(char *buf, const char *dir, const char *path)
{
    snprintf(buf, PATH_MAX, "%s%s", dir, path);
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <lower> <upper> <mount>\n", argv[0]);
        return 1;
    }

    struct mini_unionfs_state *state = malloc(sizeof(struct mini_unionfs_state));
    if (!state) {
        perror("malloc");
        return 1;
    }

    realpath(argv[1], state->lower_dir);
    realpath(argv[2], state->upper_dir);

    argv[1] = argv[3];
    argc = 2;

    return fuse_main(argc, argv, NULL, state);
}
