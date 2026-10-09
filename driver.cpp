#include "driver.h"
#include "driver.h"

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

