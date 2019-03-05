#include "ImageModel.hpp"

ImageModel::ImageModel(unsigned int width_, unsigned int height_) :
  width(width_),
  height(height_)
{
  paletteColors.reserve(16);
  for (auto i = 0u; i < 16; ++i)
  {
    paletteColors.push_back(qRgb(std::rand() % 255, std::rand() % 255, std::rand() % 255));
  }
  
  image = std::make_unique<QImage>(width, height, QImage::Format::Format_Indexed8);
  image->setColorTable(paletteColors);

  // explicitly set all pixels to avoid crashing
  memset(image->bits(), 0, image->byteCount());
}

void ImageModel::setPaletteColorAtIndex(const unsigned int index, const QRgb color)
{
  if (index >= getPaletteColorCount())
  {
    return;
  }

  paletteColors[index] = color;
  image->setColorTable(paletteColors);
  emit paletteChanged(index);
}

QRect ImageModel::setPixels(const QPoint point)
{
  // TODO: this is simulating a brush tool, move this code there later

  constexpr unsigned char brush[] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };
  auto brushStartX = -1, brushStartY = -1;
  auto brushEndX = 1, brushEndY = 1;
  const auto brushSizeX = (brushEndX - brushStartX) + 1;
  const auto brushSizeY = (brushEndY - brushStartY) + 1;

  if (point.x() + brushStartX < 0)
  {
    brushStartX = 0;
  }

  if (point.x() + brushEndX >= width)
  {
    brushEndX = 0;
  }

  if (point.y() + brushStartY < 0)
  {
    brushStartY = 0;
  }

  if (point.y() + brushEndY >= height)
  {
    brushEndY = 0;
  }

  for (auto brushY = brushStartY; brushY <= brushEndY; ++brushY)
  {
    for (auto brushX = brushStartX; brushX <= brushEndX; ++brushX)
    {
      if (brush[(brushY + 1) * brushSizeX + brushX + 1] == 1)
      {
        image->scanLine(point.y() + brushY)[point.x() + brushX] = 1;
      }
    }
  }

  emit pixelsChanged();

  return QRect(point.x() + brushStartX, point.y() + brushStartY, brushSizeX, brushSizeY);
}