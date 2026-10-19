#include <drivers/amd_am79c973.h>

using namespace MarkOS;
using namespace MarkOS::hardwarecommunication;
using namespace MarkOS::drivers;

amd_am79c973::amd_am79c973(PeripheralComponentInterconnectDeviceDescriptor *dev, InterruptManager* interrupts)
: Driver(),
  InterruptHandler(interrupts, dev->interrupt + interrupts->HardwareInterruptOffset()),

  MACAddress0Port(0x),
  MACAddress2Port(0x),
  MACAddress4Port(0x),
  registerDataPort(0x),
  registerAddressPort(0x),
  resetPort(0x),
  busControlRegisterDataPort(0x),
{

}

amd_am79c973~amd_am79c973()
{

}

void amd_am79c973::Activate()
{

}
int Reset()
{

}
common::uint32_t HandleInterrupt(common::uint32_t esp)
{

}
