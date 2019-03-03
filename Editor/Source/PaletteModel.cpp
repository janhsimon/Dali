#include "PaletteModel.hpp"

PaletteModel::PaletteModel()
{
  paletteColors.reserve(7);
  paletteColors.push_back(qRgb(255, 0, 255));
  paletteColors.push_back(qRgb(0, 128, 255));
  paletteColors.push_back(qRgb(255, 128, 20));
  paletteColors.push_back(qRgb(0, 0, 128));
  paletteColors.push_back(qRgb(150, 100, 50));
  paletteColors.push_back(qRgb(128, 128, 20));
  paletteColors.push_back(qRgb(0, 255, 128));
}

void PaletteModel::setColorAtIndex(const unsigned int index, const QRgb color)
{
  
}