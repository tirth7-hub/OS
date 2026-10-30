
#ifndef __MARKOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H
#define __MARKOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H

#include <common/types.h>
#include <gdt.h>
#include <multitasking.h>
#include <hardwarecommunication/port.h>

namespace MarkOS
{
    namespace hardwarecommunication
    {

        class InterruptManager;

        class InterruptHandler     //basic interface for hardware/software interrupt handlers
        {
        protected:
           MarkOS::common::uint8_t InterruptNumber;    //this tell which InterruptNumber belong to me
            InterruptManager* interruptManager;   //this tell which InterruptManager i belong to
            InterruptHandler(InterruptManager* interruptManager, MarkOS::common::uint8_t InterruptNumber);
            ~InterruptHandler();
        public:
            virtual MarkOS::common::uint32_t HandleInterrupt(MarkOS::common::uint32_t esp);
        };


        class InterruptManager
        {
            friend class InterruptHandler;
        protected:

            static InterruptManager* ActiveInterruptManager;
            InterruptHandler* handlers[256];
            TaskManager * taskManager;

            struct GateDescriptor  // this is cpu's format for an interrupt gate
            {
                MarkOS::common::uint16_t handlerAddressLowBits;     //low 16 bits
                MarkOS::common::uint16_t gdt_codeSegmentSelector;
                MarkOS::common::uint8_t reserved;
                MarkOS::common::uint8_t access;
                MarkOS::common::uint16_t handlerAddressHighBits;  //high 16 bits
            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                MarkOS::common::uint16_t size;
                MarkOS::common::uint32_t base;
            } __attribute__((packed));

            MarkOS::common::uint16_t hardwareInterruptOffset;
            static void SetInterruptDescriptorTableEntry(MarkOS::common::uint8_t interrupt, MarkOS::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),MarkOS::common::uint8_t DescriptorPrivilegeLevel, MarkOS::common::uint8_t DescriptorType);


            static void InterruptIgnore();

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();

            //static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x29();
            //static void HandleInterruptRequest0x0D();
            //static void HandleInterruptRequest0x0E();
            //static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x1A();
            static void HandleInterruptRequest0x1B();
            static void HandleInterruptRequest0x2B();
            static void HandleInterruptRequest0x3A();
            static void HandleInterruptRequest0x27();
            static void HandleInterruptRequest0x28();
            static void HandleInterruptRequest0x2A();
            static void HandleInterruptRequest0x36();
            static void HandleInterruptRequest0x1D();
            static void HandleInterruptRequest0x5B();
            static void HandleInterruptRequest0x38();
            static void HandleInterruptRequest0x4B();
            static void HandleInterruptRequest0x50();
            //static void HandleInterruptRequest0x48();
            //static void HandleInterruptRequest0x4D();



            static void HandleInterruptRequest0x45();
            static void HandleInterruptRequest0x47();
            static void HandleInterruptRequest0x48();
            static void HandleInterruptRequest0x49();
            static void HandleInterruptRequest0x4D();
            static void HandleInterruptRequest0x4C();
            //static void HandleInterruptRequest0x4B();
            static void HandleInterruptRequest0x51();
            static void HandleInterruptRequest0x4F();
            static void HandleInterruptRequest0x52();
            static void HandleInterruptRequest0x53();
            static void HandleInterruptRequest0x4E();
            static void HandleInterruptRequest0x4A();
            static void HandleInterruptRequest0x37();

            static void HandleInterruptRequest0x80();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static MarkOS::common::uint32_t HandleInterrupt(MarkOS::common::uint8_t interrupt, MarkOS::common::uint32_t esp);
            MarkOS::common::uint32_t DoHandleInterrupt(MarkOS::common::uint8_t interrupt, MarkOS::common::uint32_t esp);

            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;

        public:
            InterruptManager(MarkOS::common::uint16_t hardwareInterruptOffset, MarkOS::GlobalDescriptorTable* globalDescriptorTable, MarkOS::TaskManager* taskManager);
            ~InterruptManager();
            MarkOS::common::uint16_t HardwareInterruptOffset();
            void Activate();
            void Deactivate();
        };
    }
}
#endif
