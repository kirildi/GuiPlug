#include "SkiaHandler.hpp"

GUIPLUG::SkiaHandler::SkiaHandler(){};
GUIPLUG::SkiaHandler::~SkiaHandler(){};

void GUIPLUG::SkiaHandler::draw(int width, int height)
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