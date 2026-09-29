#include "gdt.h"

GlobalDescriptorTable: GlobalDescriptorTable()
:nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentselector(0,64*1024*1024,0x9A),
dataSegmentSelector(0,6*1024*1024,0x92)
{
    //elling procerssor to used this table, beacuse processor it exccept 6byte in row
    uint32_t i[2];
    i[0]= (uint32_t)this;
    i[1]=sizeof(GlobalDescriptorTable) << 16; //swift to left

    asm volatile("lgdt (%0)" : : "p" (((uint8_t *) i )+2));


}
GlobalDescriptorTable::~GlobalDescriptorTable()  //destructor
{

}
uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this; //here this means GlobalDescriptorTable
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
    return (uint8_t*)&CodeSegmentSelector - (uint8_t*)this; //here this means GlobalDescriptorTable
}
//setting entries

GlobalDescriptorTable::SegmentSelector(uint32_t base, uint32_t limit, uint8_t flags)
{
    uint8_t* target = (uint8_t*)this;   //here this means GlobalDescriptorTable

    if(limit <= 65536)
    {
        target[6] = 0x40; //tell processor this is 16 bit entry

    }else{

    }
}
