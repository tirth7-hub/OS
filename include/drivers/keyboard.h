
#ifndef __MARKOS__DRIVERS__KEYBOARD_H
#define __MARKOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace MarkOS
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public MarkOS::hardwarecommunication::InterruptHandler, public Driver
        {
            MarkOS::hardwarecommunication::Port8Bit dataport;
            MarkOS::hardwarecommunication::Port8Bit commandport;

            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(MarkOS::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual MarkOS::common::uint32_t HandleInterrupt(MarkOS::common::uint32_t esp);
            virtual void Activate();
        };

    }
}


#endif
