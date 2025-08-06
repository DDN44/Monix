#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include "brick.h"

#define BLKNUM 4096 //2mb
#define BRKSIZE 2

brickheader_t *makesuper()
{
    brickheader_t *super = malloc(512);

    super->magic = MAGIC;
    super->blocknum = BLKNUM;
    super->blocksize = 512;
    super->bricksize = BRKSIZE;
    super->alocblk = 1;
    super->alocsize = 8;
    super->rootblk = 9;
    super->rootentnum = 32;
    return super;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Please input filename\n");
        return 1;
    }

    FILE *fd = fopen(argv[1], "r+");

    for(int i=0; i < BLKNUM * 512; i++)
    {
        fputc(0, fd);
    }

    rewind(fd);

    brickheader_t *sup = makesuper();

    fwrite(sup, 512, 1, fd);

    fseek(fd, 512, SEEK_SET);

    fputc(0xFF, fd);
    fputc(0xFF, fd);

    fflush(fd);

    rewind(fd);

    for(int i=0; i < 512; i++)
    {
        printf("%x", fgetc(fd));
    }
    printf("\n");

    fclose(fd);
    return 0;
}