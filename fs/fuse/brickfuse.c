#define FUSE_USE_VERSION 31
#include <sys/vfs.h>
#include <fuse.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "brick.h"

brickheader_t state;

uint16_t *alocbrk;

brickent_t *root;

FILE *fd;

int findentname(const char *str)
{
    const char *basename = strrchr(str, '/');
    if(!basename)
        basename = str;
    else
        basename++;

    for(int i=0; i < 32; i++)
    {
        char namebuf[24];
        memcpy(namebuf, root[i].name, 23);
        namebuf[23] = '\0';
        if(strcmp(str, root[i].name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int brickattr(const char *str, struct stat *st)
{
    memset(st, 0, sizeof(struct stat));

    if(strcmp("/", str) == 0)
    {
        st->st_mode = __S_IFDIR | 0766;
        st->st_nlink = 2;
        return 0;
    }

    int ent = findentname(str);

    if(ent != -1)
    {
        st->st_mode = __S_IFREG | 0766;
        st->st_nlink = 1;
        st->st_size = root[ent].size;
        return 0;
    }
    return -ENOENT;
}

int brickdir(const char *str, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fuseinfo)
{
    char temp[24];
    if (fill(buf, ".", NULL, 0) != 0)
        return 0;
    if (fill(buf, "..", NULL, 0) != 0)
        return 0;

    for(int i=offset; i < 32; i++)
    {
        if(root[i].type != 0)
        {
            memcpy(temp, root[i].name, 23);
            temp[23] = '\0';
            fill(buf, temp, 0, 0);
        }
    }

    return 0;
}

uint32_t findfreebrick()
{
    for(int i=0; i < 2048; i++)
    {
        if(alocbrk[i] == 0)
        {
            return i;
        }
    }
}

int brickcreate(const char *str, mode_t mode, struct fuse_file_info *fileinfo)
{
    uint8_t fmd;
    if((mode & __S_IFDIR) != 0)
    {
        fmd = ENTDIR;
    }
    if((mode & __S_IFREG) != 0)
    {
        fmd = ENTFILE;
    }

    for(int i=0; i < 32; i++)
    {
        if(root[i].type == 0)
        {
            root[i].type = fmd;
            root[i].bricknum = findfreebrick();
            root[i].size = 0;

            strcpy(root[i].name, str);
            return 0;
        }
    }
}

int brickopen(const char *str, struct fuse_file_info *fileinfo)
{
    if(findentname(str) == -1)
        return -ENOENT;

    if((fileinfo->flags & O_ACCMODE) != O_RDWR)
        return -EACCES;

    return 0;
}

int brickutimens(const char *str, const struct timespec tv[2])
{
    return 0;
}

int brickread(const char *str, char *buf, size_t size, off_t offset, struct fuse_file_info *fileinfo)
{
    int ent = findentname(str);
    if(ent = -ENOENT)
    {
        return -ENOENT;
    }
    if(offset >= root[ent].size)
    {
        return 0;
    }
    if(offset + size > root[ent].size)
    {
        size = root[ent].size - offset;
    }
    uint8_t *readtemp = malloc(root[ent].size);
    
    memcpy(buf, readtemp + offset, size);
}

static struct fuse_operations brickoper = {
    .getattr = brickattr,
    .readdir = brickdir,
    .create = brickcreate,
    .open = brickopen,
    .utimens = brickutimens,
    .read = brickread,
};

int main(int argc, char **argv)
{
    //if(argc < 2)
    //{
    //    printf("Please input file path\n");
    //    return 1;
    //}

    fd = fopen("/dev/sdd", "r+");

    brickheader_t *buf = malloc(512);

    fread(buf, 512, 1, fd);

    printf("%x\n", buf->magic);

    fseek(fd, buf->alocblk * buf->blocksize, SEEK_SET);

    alocbrk = malloc(buf->blocksize * buf->alocsize);

    fread(alocbrk, buf->blocksize, buf->alocsize, fd);

    printf("%x", *alocbrk);

    fseek(fd, buf->rootblk * buf->blocksize, SEEK_SET);

    root = malloc(buf->rootentnum * 32);

    fread(root, buf->blocksize, 2, fd);

    fuse_main(argc, argv, &brickoper, NULL);

    fclose(fd);
    return 0;
}