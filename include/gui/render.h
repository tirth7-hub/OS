#ifndef __MARKOS__GUI__RENDER_H
#define __MARKOS__GUI__RENDER_H

#include <drivers/vga.h>
#include <common/graphicscontext.h>

namespace MarkOS{
    namespace gui{

        class Pixel{
        public:
            MarkOS::common::uint8_t r;
            MarkOS::common::uint8_t g;
            MarkOS::common::uint8_t b;
        };

        class Render : public MarkOS::drivers::VideoGraphicsArray{
        private:
            Pixel pixels[320][200];

        public:
            Render(
                common::int32_t w, common::int32_t h
            );

            ~Render();

            void display(common::GraphicsContext* gc);

            void PutPixel(MarkOS::common::int32_t x, MarkOS::common::int32_t y, MarkOS::common::uint8_t r, MarkOS::common::uint8_t g, MarkOS::common::uint8_t b);
        };
    }
}


#endif
