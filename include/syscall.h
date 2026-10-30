#ifndef __MARKOS__SYSCALL_H
#define __MARKOS__SYSCALL_H
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking.h>
namespace MarkOS
{
    class SyscalHandler : public hardwarecommunication::InterruptHandler
    {
    public:
        SyscalHandler(hardwarecommunication::InterruptManager* interruptManager, MarkOS::common::uint8_t InterruptNumber);
        ~SyscalHandler();

        virtual MarkOS::common::uint32_t HandlerInterrupt(MarkOS::common::uint32_t esp);
    };


}
#endif
