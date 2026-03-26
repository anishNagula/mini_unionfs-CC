#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct mini_unionfs_state {
    char lower_dir[PATH_MAX];
    char upper_dir[PATH_MAX];
};

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

    printf("Lower: %s\nUpper: %s\nMount: %s\n", argv[1], argv[2], argv[3]);

    return fuse_main(argc, argv, NULL, state);
}
