#include <stdint.h>

typedef struct {
    uint8_t oemstr[8];
    uint16_t sectorbytes 512;
    uint8_t sectorperclust 4;
    uint16_t reservedsectors 4;
    uint8_t fatnum 2;
    uint16_t rootentries 512;
    uint16_t totalsectors 49984;
    uint8_t type 0xF8;
    uint16_t sectorsperfat 52;
    uint16_t sectorspertrack 32;
    uint16_t headsorsides 4;
    uint32_t hiddensectors 0;
    uint32_t largesectors 0;
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