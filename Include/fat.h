#include <stdint.h>

#ifndef _FAT_H_
#define _FAT_H_

typedef struct {
    uint8_t na;
    uint8_t na2;
    uint8_t na3;
    uint8_t oemstr[8];
    uint16_t sectorbytes;
    uint8_t sectorperclust;
    uint16_t reservedsectors;
    uint8_t fatnum;
    uint16_t rootentries;
    uint16_t totalsectors;
    uint8_t type;
    uint16_t sectorsperfat;
    uint16_t sectorspertrack;
    uint16_t headsorsides;
    uint32_t hiddensectors;
    uint32_t largesectors;
}__attribute__((packed)) fatbpb_t;

typedef struct {
    uint8_t drivenum;
    uint8_t reserved;
    uint8_t signature; //must be 0x28 or 0x29
    uint32_t volumeid;
    uint8_t label[11];
    uint8_t identifier[8];
}__attribute__((packed)) fatebr_t;

typedef struct {
    uint8_t name[11];
    uint8_t attribute;
    uint8_t reserved;
    uint8_t seconds;
    uint16_t time;
    uint16_t date;
    uint16_t accessdate;
    uint16_t clusthigh;
    uint16_t modtime;
    uint16_t moddate;
    uint16_t clustlow;
    uint32_t size;
}__attribute__((packed)) fatstd_t; //8.3 fat descriptor format

typedef struct {
    uint8_t order;
    uint16_t name1[5];
    uint8_t attribute;
    uint8_t type;
    uint8_t checksum;
    uint16_t name2[6];
    uint16_t zero;
    uint16_t name3[2];
}__attribute__((packed)) fatlfn_t; //Long File Name Entry

void fat_init();
fatstd_t *fat_get_entry(uint8_t *str);
void fat_dir_list();
void *fat_load_file(uint8_t *str);

#endif