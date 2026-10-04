#ifndef __GDT_H
#define __GDT_H

#include "types.h"

class GlobalDescriptorTable
{
public:

    class SegmentDescriptor //class fro entries
    {
    private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t limit_hi;
        uint8_t base_vhi;

    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);//constructor
        uint32_t Base();
        uint32_t Limit();
    } __attribute__((packed));   // this tell compiler don't insert padding bytes

private:
    SegmentDescriptor nullSegmentSelector;  //entry 0 -> null
    SegmentDescriptor unusedSegmentSelector; //entry 1 -> unused
    SegmentDescriptor codeSegmentSelector;  //entry 2 -> code
    SegmentDescriptor dataSegmentSelector;  //entry 3 -> data

public:

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};

#endif
