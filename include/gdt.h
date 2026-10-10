#ifndef __MARKOS__GDT_H
#define __MARKOS__GDT_H

#include <common/types.h>

namespace MarkOS
{

    class GlobalDescriptorTable
    {
    public:

        class SegmentDescriptor
        {
        private:
            MarkOS::common::uint16_t limit_lo;
            MarkOS::common::uint16_t base_lo;
            MarkOS::common::uint8_t base_hi;
            MarkOS::common::uint8_t type;
            MarkOS::common::uint8_t limit_hi;
            MarkOS::common::uint8_t base_vhi;

        public:
            SegmentDescriptor(MarkOS::common::uint32_t base, MarkOS::common::uint32_t limit, MarkOS::common::uint8_t type);
            MarkOS::common::uint32_t Base();
            MarkOS::common::uint32_t Limit();
        } __attribute__((packed));

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        MarkOS::common::uint16_t CodeSegmentSelector();
        MarkOS::common::uint16_t DataSegmentSelector();
    };

}

#endif
