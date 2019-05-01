#include "BrushModel.hpp"

#include <cassert>

BrushModel::BrushModel() :
  width(7),
  height(7)
{
  colors.reserve(2);
  colors.push_back(qRgba(0, 0, 0, 0));
  colors.push_back(qRgba(0, 0, 0, 255));

  brush = std::make_unique<QImage>(width, height, QImage::Format::Format_Indexed8);
  brush->setColorTable(colors);

  memset(brush->bits(), 0, brush->sizeInBytes());
  setBrushAt(0, 0, true);
}

bool BrushModel::getBrushAt(const int x, const int y) const
{
  assert(x >= 0 && x < width);
  assert(y >= 0 && y < height);
  return brush->constScanLine(y)[x] != 0;
}

void BrushModel::setBrushAt(const int x, const int y, const bool value)
{
  assert(x >= 0 && x < width);
  assert(y >= 0 && y < height);
  brush->scanLine(y)[x] = static_cast<int>(value);

  //emit brushChanged();
}

void BrushModel::setColor(QRgb color)
{
  assert(colors.size() == 2);
  colors[1] = color;

  brush->setColorTable(colors);

  emit colorChanged();
}