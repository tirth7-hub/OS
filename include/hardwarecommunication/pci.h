#ifndef __MARKOS__HARDWARECOMMUNICATION__PCI_H
#define __MARKOS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>

namespace MarkOS
{
    namespace hardwarecommunication
    {
        enum BaseAddressRegisterType
        {
            MemoryMapping =0,
            InputOutput = 1

        };

        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            MarkOS::common::uint8_t* address;
            MarkOS::common::uint32_t size;
            BaseAddressRegisterType type;

        };


        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            MarkOS::common::uint32_t portBase;
            MarkOS::common::uint32_t interrupt;

            MarkOS::common::uint16_t bus;
            MarkOS::common::uint16_t device;
            MarkOS::common::uint16_t function;

            MarkOS::common::uint16_t vendor_id;
            MarkOS::common::uint16_t device_id;

            MarkOS::common::uint8_t class_id;
            MarkOS::common::uint8_t subclass_id;
            MarkOS::common::uint8_t interface_id;

            MarkOS::common::uint8_t revision;

            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();

        };


        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;

        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            MarkOS::common::uint32_t Read(MarkOS::common::uint16_t bus, MarkOS::common::uint16_t device, MarkOS::common::uint16_t function, MarkOS::common::uint32_t registeroffset);

            void Write(MarkOS::common::uint16_t bus, MarkOS::common::uint16_t device, MarkOS::common::uint16_t function, MarkOS::common::uint32_t registeroffset, MarkOS::common::uint32_t value);

            bool DeviceHasFunctions(MarkOS::common::uint16_t bus, MarkOS::common::uint16_t device);

            void SelectDrivers(MarkOS::drivers::DriverManager* driverManager, MarkOS::hardwarecommunication::interruptManager* interrupts);


            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(MarkOS::common::uint16_t bus, MarkOS::common::uint16_t device, MarkOS::common::uint16_t function);


            MarkOS::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor, MarkOS::hardwarecommunication::interruptManager* interrupts);



            BaseAddressRegister GetBaseAddressRegister(MarkOS::common::uint16_t bus, MarkOS::common::uint16_t device, MarkOS::common::uint16_t function, MarkOS::common::uint16_t bar);
        };

    }
}

#endif
