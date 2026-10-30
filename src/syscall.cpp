
#include <syscall.h>
using namespace MarkOS;
using namespace MarkOS::common;
using namespace MarkOS::hardwarecommunication;

SyscalHandler::SyscalHandler(hardwarecommunication::InterruptManager* interruptManager, MarkOS::common::uint8_t InterruptNumber)
:   InterruptHandler(interruptManager, InterruptNumber+interruptManager->HardwareInterruptOffset())
{

}
SyscalHandler::~SyscalHandler()
{

}
void printf(char*);
uint32_t SyscalHandler::HandlerInterrupt(MarkOS::common::uint32_t esp)
{

    CPUState* cpu = (CPUState*)esp;

    switch(cpu->eax)
    {
        case 4:
            printf((char*)cpu->ebx);
            break;
        default:
            break;
    }

    return esp;

}
