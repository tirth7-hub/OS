#ifndef __MARKOS__DRIVERS__AM79C973_H
#define __MARKOS__DRIVERS__AM79C973_H

#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <hardwarecommunication/port.h>
#include <common/types.h>
#include <drivers/driver.h>

namespace MarkOS
{
    namespace drivers
    {
        class amd_am79c973 : public Driver , public hardwarecommunication::InterruptHandler
        {
            struct InitializationBlock
            {
                common::uint16_t mode;
                unsigned reserved1 : 4;
                unsigned numSendBuffers : 4;
                unsigned reserved2 : 4;
                unsigned  numRecvBuffers : 4;
                common::uint64_t physicalAddress : 48;
                common::uint16_t reserved3;
                common::uint64_t logicalAddress;
                common::uint32_t recvBufferDescrAddress;
                common::uint32_t sendBufferDescrAddress;


            } __attribute__((packed));

            struct BufferDescriptor
            {

                common::uint32_t address;
                common::uint32_t flags;
                common::uint32_t flags2;
                common::uint32_t avail;
            } __attribute__((packed));



            hardwarecommunication::Port16Bit MACAddress0Port;
            hardwarecommunication::Port16Bit MACAddress2Port;
            hardwarecommunication::Port16Bit MACAddress4Port;
            hardwarecommunication::Port16Bit registerDataPort;
            hardwarecommunication::Port16Bit registerAddressPort;
            hardwarecommunication::Port16Bit resetPort;
            hardwarecommunication::Port16Bit busControlRegisterDataPort;

            InitializationBlock initBlock;


            BufferDescriptor* sendBufferDescr;
            common::uint8_t sendBuffersDescMemory[2024+15];
            common::uint8_t sendBuffers[2*1024+15][8];
            common::uint8_t currentSendBuffer;

            BufferDescriptor* recvBufferDescr;
            common::uint8_t recvBuffersDescMemory[2024+15];
            common::uint8_t recvBuffers[2*1024+15][8];
            common::uint8_t currentRecvBuffer;



        public:
            amd_am79c973(MarkOS::hardwarecommunication::PeripheralComponentInterconnectDeviceDescriptor *dev,MarkOS::hardwarecommunication::InterruptManager* interrupts);
            ~amd_am79c973();

            void Activate();
            int Reset();
            common::uint32_t HandleInterrupt(common::uint32_t esp);

            void Send(common::uint8_t* buffer, int size);
            void Recieve();
        };
    }
}
#endif
