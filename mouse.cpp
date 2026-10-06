
#include "mouse.h"

MouseDriver::MouseDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x2), // 0x21 is the interriptNumber for keyboard, this act as a bridge b/w generic interrupt and specific keyboard driver
dataport(0x60), //0x60 is memory address of keyboard port
commandport(0x64) //0x64 is memory address of keyboard controller port
{
    offset = 0;
    buttons= 0;
    uint16_t* VideoMemory = (uint16_t*)0xb8000;

    VideoMemory[80*12+40] = ((VideoMemory[80*12+40] & 0xF000) >> 4)
                        | ((VideoMemory[80*12+40] & 0x0F00) << 4)
                        | ((VideoMemory[80*12+40] & 0x00FF));


    commandport.Write(0xAB); // tell keyboard controller to enable the keyboard interface
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 2); //modifies that command byte
    commandport.Write(0x60); // this code means that write a new controller commmand byte
    dataport.Write(status); //writes it

    commandport.Write(0xD4);
    dataport.Write(0xF4);//enable keyboard scanning on standerd PS
    dataport.Read();

}

MouseDriver::~MouseDriver()
{
}

void printf(char*);

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{

    uint8_t status = commandport.Read();
    if(!(status & 0x20))
        return esp;

    static uint8_t x=40,y=12;


    buffer[offset] = dataport.Read();
    offset = (offset +1) % 3;
    if(offset == 0){
        uint16_t* VideoMemory = (uint16_t*)0xb8000;


        VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                            | ((VideoMemory[80*y+x] & 0x0F00) << 4)
                            | ((VideoMemory[80*y+x] & 0x00FF));


        x += buffer[1];
        if(x<0) x =0;
        if(x>=80) x=79;


        y -= buffer[2];
        if(y<0) y =0;
        if(y>=25) y=24;

        VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                            | ((VideoMemory[80*y+x] & 0x0F00) << 4)
                            | ((VideoMemory[80*y+x] & 0x00FF));


        for(uint8_t i =0;i<3;i++){
            if((buffer[0] & (0x01<<i)) != (buttons & (0x01<<i)))
                VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                                    | ((VideoMemory[80*y+x] & 0x0F00) << 4)
                                    | ((VideoMemory[80*y+x] & 0x00FF));
        }
        buttons = buffer[0];
    }
    return esp;
}
