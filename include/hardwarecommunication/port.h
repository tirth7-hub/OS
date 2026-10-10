
#ifndef __MARKOS__HARDWARECOMMUNICATION__PORT_H
#define __MARKOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace MarkOS
{
    namespace hardwarecommunication
    {

        class Port
        {
        protected:
            Port(MarkOS::common::uint16_t portnumber);
            // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
            ~Port();
            MarkOS::common::uint16_t portnumber;
        };


        class Port8Bit : public Port
        {
        public:
            Port8Bit(MarkOS::common::uint16_t portnumber);
            ~Port8Bit();

            virtual MarkOS::common::uint8_t Read();//This means the class has a function that reads one byte from the hardware port.
            virtual void Write(MarkOS::common::uint8_t data); //This sends one byte to the hardware port.

        protected:
            static inline MarkOS::common::uint8_t Read8(MarkOS::common::uint16_t _port) //make variable result(c++) -> set an mrmory address in result(Asemmbly lang.) ans store that address in result -> now return result(c++)
            {
                MarkOS::common::uint8_t result;
                __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));//"inb"-Read one byte from an I/O port.
                return result;
            }

            static inline void Write8(MarkOS::common::uint16_t _port, MarkOS::common::uint8_t _data)
            {
                __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));//"outb"-Send one byte to an I/O port.
            }
        };



        class Port8BitSlow : public Port8Bit   //The reason is that some old hardware controllers need a little time between commands
        {
        public:
            Port8BitSlow(MarkOS::common::uint16_t portnumber);
            ~Port8BitSlow();

            virtual void Write(MarkOS::common::uint8_t data);
        protected:
            static inline void Write8Slow(MarkOS::common::uint16_t _port, MarkOS::common::uint8_t _data)
            {
                __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port)); //This jumps introduce a tiny delay.
            }

        };



        class Port16Bit : public Port
        {
        public:
            Port16Bit(MarkOS::common::uint16_t portnumber);
            ~Port16Bit();

            virtual MarkOS::common::uint16_t Read();
            virtual void Write(MarkOS::common::uint16_t data);

        protected:
            static inline MarkOS::common::uint16_t Read16(MarkOS::common::uint16_t _port)
            {
                MarkOS::common::uint16_t result;
                __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                return result;
            }

            static inline void Write16(MarkOS::common::uint16_t _port, MarkOS::common::uint16_t _data)
            {
                __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
            }
        };



        class Port32Bit : public Port
        {
        public:
            Port32Bit(MarkOS::common::uint16_t portnumber);
            ~Port32Bit();

            virtual MarkOS::common::uint32_t Read();
            virtual void Write(MarkOS::common::uint32_t data);

        protected:
            static inline MarkOS::common::uint32_t Read32(MarkOS::common::uint16_t _port)
            {
                MarkOS::common::uint32_t result;
                __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                return result;
            }

            static inline void Write32(MarkOS::common::uint16_t _port, MarkOS::common::uint32_t _data)
            {
                __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
            }
        };
    }
}


#endif
