#ifndef SKIA_HANDLER_H
#define SKIA_HANDLER_H

#include <vector>
#include "SkCanvas.h"
#include "SkSurface.h"
#include "SkPaint.h"
#include "SkRect.h"
#include "SkImage.h"
#include "SkImageInfo.h"

namespace GUIPLUG
{

      class SkiaHandler
      {

      public:
            SkiaHandler(){

            };
            ~SkiaHandler(){};
            void draw(int width, int height)
            {
                  surface = SkSurface::MakeRasterN32Premul(width, height);

                  auto canvas = surface->getCanvas();
                  sk_sp<SkSurface> big(SkSurface::MakeRasterN32Premul(64, 64));
                  sk_sp<SkSurface> lil(big->makeSurface(SkImageInfo::MakeN32(32, 32, kPremul_SkAlphaType)));
                  big->getCanvas()->clear(SK_ColorRED);
                  lil->getCanvas()->clear(SK_ColorBLACK);
                  sk_sp<SkImage> early(big->makeImageSnapshot());
                  lil->draw(big->getCanvas(), 16, 16);
                  sk_sp<SkImage> later(big->makeImageSnapshot());
                  canvas->drawImage(early, 0, 0);
                  canvas->drawImage(later, 128, 0);
            }
            // surface = SkSurface::MakeRasterN32Premul(width, height);

            // auto canvas = surface->getCanvas();

            // // Clear background
            // canvas->clear(SK_ColorWHITE);

            // SkPaint paint;
            // paint.setColor(SK_ColorRED);

            // // Draw a rectangle with red paint
            // SkRect rect = SkRect::MakeXYWH(10, 10, 128, 128);
            // canvas->drawRect(rect, paint);

      private:
            sk_sp<SkSurface> surface{};
      };
}
#endif // SKIA_HANDLER_H