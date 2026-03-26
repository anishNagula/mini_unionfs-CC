CC=gcc
CFLAGS=-Wall -Wextra -O2
FUSE_FLAGS=`pkg-config fuse3 --cflags --libs`

TARGET=mini_unionfs
SRC=src/mini_unionfs.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(FUSE_FLAGS)

clean:
	rm -f $(TARGET)
