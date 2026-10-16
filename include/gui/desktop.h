#ifndef __MARKOS__GUI__DESKTOP_H
#define __MARKOS__GUI__DESKTOP_H


#include <gui/widget.h>
#include <drivers/mouse.h>

namespace MarkOS
{
    namespace gui
    {
        class Desktop : public CompositeWidget, public MarkOS::drivers::MouseEventHandler
        {
        protected:
            common::uint32_t MouseX;
            common::uint32_t MouseY;

        public:
            Desktop(common::uint32_t w, common::uint32_t h, common::uint8_t r, common::uint8_t g, common::uint8_t b);
            ~Desktop();

            void Draw (common::GraphicsContext* gc);

            void OnMouseDown(MarkOS::common::uint8_t  button);
            void OnMouseUp(MarkOS::common::uint8_t button);
            void OnMouseMove(int x, int y);
        };
    }
}

#endif
