#ifndef __MARKOS__DRIVERS__DRIVER_H
#define __MARKOS__DRIVERS__DRIVER_H

namespace MarkOS
{
    namespace drivers
    {

        class Driver{
        public:
            Driver();
            ~Driver();
            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager
        {
        private:
            Driver* drivers[255];
            int numdrivers;
        public:
            DriverManager();
            void AddDriver(Driver*);
            void ActivateAll();



        };

    }
}


#endif
