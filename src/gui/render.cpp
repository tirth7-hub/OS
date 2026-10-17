#include <gui/render.h>

using namespace MarkOS;
using namespace MarkOS::common;
using namespace MarkOS::gui;


Render::Render(common::int32_t w, common::int32_t h)
{
    //Pixel[w][h] pixel;
}
Render::~Render()
{

}

void Render::display(common::GraphicsContext* gc)
{
    for(int ix=0;ix<320;ix++){
        for(int iy=0;iy<200;iy++){
            gc->PutPixel(ix,iy,pixels[ix][iy].r, pixels[ix][iy].g, pixels[ix][iy].b);

        }
    }
}
void Render::PurPixel(MarkOS::common::int32_t x, MarkOS::common::int32_t y,  MarkOS::common::int8_t r, MarkOS::common::int8_t g, MarkOS::common::int8_t b)
{
    pixels[x][y].r = r;
    pixels[x][y].g = g;
    pixels[x][y].b = b;
}
