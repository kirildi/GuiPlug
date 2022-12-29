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
            SkiaHandler();
            ~SkiaHandler();
            void draw(int width, int height);

      private:
            sk_sp<SkSurface> surface{};
      };
}
#endif // SKIA_HANDLER_H