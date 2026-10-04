
#ifndef __PORT_H
#define __PORT_H

#include "types.h"


class Port
{
protected:
    Port(uint16_t portnumber);
    // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
    ~Port();
    uint16_t portnumber;
};


class Port8Bit : public Port
{
public:
    Port8Bit(uint16_t portnumber);
    ~Port8Bit();

    virtual uint8_t Read();//This means the class has a function that reads one byte from the hardware port.
    virtual void Write(uint8_t data); //This sends one byte to the hardware port.

protected:
    static inline uint8_t Read8(uint16_t _port) //make variable result(c++) -> set an mrmory address in result(Asemmbly lang.) ans store that address in result -> now return result(c++)
    {
        uint8_t result;
        __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));//"inb"-Read one byte from an I/O port.
        return result;
    }

    static inline void Write8(uint16_t _port, uint8_t _data)
    {
        __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));//"outb"-Send one byte to an I/O port.
    }
};



class Port8BitSlow : public Port8Bit   //The reason is that some old hardware controllers need a little time between commands
{
public:
    Port8BitSlow(uint16_t portnumber);
    ~Port8BitSlow();

    virtual void Write(uint8_t data);
protected:
    static inline void Write8Slow(uint16_t _port, uint8_t _data)
    {
        __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port)); //This jumps introduce a tiny delay.
    }

};



class Port16Bit : public Port
{
public:
    Port16Bit(uint16_t portnumber);
    ~Port16Bit();

    virtual uint16_t Read();
    virtual void Write(uint16_t data);

protected:
    static inline uint16_t Read16(uint16_t _port)
    {
        uint16_t result;
        __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write16(uint16_t _port, uint16_t _data)
    {
        __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
    }
};



class Port32Bit : public Port
{
public:
    Port32Bit(uint16_t portnumber);
    ~Port32Bit();

    virtual uint32_t Read();
    virtual void Write(uint32_t data);

protected:
    static inline uint32_t Read32(uint16_t _port)
    {
        uint32_t result;
        __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write32(uint16_t _port, uint32_t _data)
    {
        __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
    }
};




#endif
