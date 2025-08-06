#include <stdker.h>
#include <ata.h>
#include <serial.h>
#include <mem.h>

#define PIOREAD48 0x24

void ata_poll()
{
    uint8_t polling = 1;
    uint8_t status;
    while(polling == 1)
    {
        //ser_printk("P");
        status = inb(0x1F0 + 7);
        if((status & 0x80) == 0 && (status & 8) == 8)
        {
            polling = 0;
            //ser_printk("polling done\n");
        }
    }
}

void ata_sendreq(uint64_t lba, uint16_t sectcount, uint8_t reqtype)
{
    uint8_t sectlow = sectcount & 0xFF;
    uint8_t secthigh = (sectcount >> 8) & 0xFF;

    uint8_t lba1 = 0;
    uint8_t lba2 = 0;
    uint8_t lba3 = 0;
    uint8_t lba4 = 0;
    uint8_t lba5 = 0;
    uint8_t lba6 = 0;

    lba1 = lba & 0xFF;
    lba2 = (lba >> 8)& 0xFF;
    lba3 = (lba >> 16)& 0xFF;
    lba4 = (lba >> 24)& 0xFF;
    lba5 = (lba >> 32)& 0xFF;
    lba6 = (lba >> 40)& 0xFF;

    outb(0x1F6, 0x40);

    outb(0x1F2, secthigh);
    outb(0x1F3, lba4);
    outb(0x1F4, lba5);
    outb(0x1F5, lba6);

    outb(0x1F2, sectlow);
    outb(0x1F3, lba1);
    outb(0x1F4, lba2);
    outb(0x1F5, lba3);

    outb(0x1F7, reqtype);
}

void ata_read(uint64_t lba, uint16_t sectcount, uint8_t *buffer)
{
    ata_sendreq(lba, sectcount, PIOREAD48);
    for(uint16_t i = 0; i < sectcount; i++)
    {
        ata_poll();
        uint32_t nblk = i * 512;
        uint16_t iblk = 0;
        uint16_t temp = 0;
        while(iblk < 512)
        {
            temp = inw(0x1F0);
            buffer[iblk + nblk] = temp & 0xFF;
            buffer[(iblk + 1) + nblk] = (temp >> 8) & 0xFF;
            iblk += 2;
        }
    }
}


mbrpart_t *ata_getprimary()
{
    uint8_t *mbr = mem_alloc_heap(512);
    //mbrpart_t *prim = ;
    
    ata_read(0, 1, mbr);

    //for(uint16_t i=0; i < 512; i++)
    //{
    //    printk("%d", mbr[i]);
    //}

    //prim.type = mbr[4 + 0x1BE];
    //prim.lba = mbr[8 + 0x1BE];
    //prim.sects = mbr[12 + 0x1BE];

    return (mbrpart_t *)(mbr + 0x1BE);
}

void ata_init()
{
    
}