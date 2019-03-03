#include "ImageModel.hpp"

ImageModel::ImageModel(unsigned int width_, unsigned int height_, const PaletteModel* paletteModel) :
  width(width_),
  height(height_)
{
  image = std::make_unique<QImage>(width, height, QImage::Format::Format_Indexed8);
  image->setColorTable(paletteModel->getPaletteColors());

  // explicitly set all pixels to avoid crashing
  memset(image->bits(), 0, image->byteCount());
}

QRect ImageModel::setPixels(int x, int y)
{
  // TODO: this is simulating a brush tool, move this code there later

  constexpr unsigned char brush[] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };
  auto brushStartX = -1, brushStartY = -1;
  auto brushEndX = 1, brushEndY = 1;
  const auto brushSizeX = (brushEndX - brushStartX) + 1;
  const auto brushSizeY = (brushEndY - brushStartY) + 1;

  if (x + brushStartX < 0)
  {
    brushStartX = 0;
  }

  if (x + brushEndX >= width)
  {
    brushEndX = 0;
  }

  if (y + brushStartY < 0)
  {
    brushStartY = 0;
  }

  if (y + brushEndY >= height)
  {
    brushEndY = 0;
  }

  for (auto brushY = brushStartY; brushY <= brushEndY; ++brushY)
  {
    for (auto brushX = brushStartX; brushX <= brushEndX; ++brushX)
    {
      if (brush[(brushY + 1) * brushSizeX + brushX + 1] == 1)
      {
        image->scanLine(y + brushY)[x + brushX] = 1;
      }
    }
  }

  emit pixelsChanged();

  return QRect(x + brushStartX, y + brushStartY, brushSizeX, brushSizeY);
}