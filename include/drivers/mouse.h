
#ifndef __MARKOS__DRIVERS__MOUSE_H
#define __MARKOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace MarkOS
{
    namespace drivers
    {

        class MouseEventHandler
        {
        public:
            MouseEventHandler();
            virtual void OnActivate();
            virtual void OnMouseDown(MarkOS::common::uint8_t  button);
            virtual void OnMouseUp(MarkOS::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };



        class MouseDriver : public MarkOS::hardwarecommunication::InterruptHandler, public Driver
        {
            MarkOS::hardwarecommunication::Port8Bit dataport;
            MarkOS::hardwarecommunication::Port8Bit commandport;
            MarkOS::common::uint8_t buffer[3];
            MarkOS::common::uint8_t offset;
            MarkOS::common::uint8_t buttons;
            MouseEventHandler* handler;

        public:
            MouseDriver(MarkOS::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual MarkOS::common::uint32_t HandleInterrupt(MarkOS::common::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif
