#include <drivers/driver.h>

using namespace MarkOS::drivers;

Driver::Driver(){

}
Driver::~Driver()
{

}
void Driver::Activate()
{

}
int Driver::Reset()
{
    return 0;
}
void Driver::Deactivate()
{

}

DriverManager::DriverManager()
{
    numdrivers = 0;
}
void DriverManager::AddDriver(Driver* drv)
{
    drivers[numdrivers] = drv;
    numdrivers++;
}
void DriverManager::ActivateAll()
{
        for(int i=0; i<numdrivers; i++)
            drivers[i]->Activate();

}

