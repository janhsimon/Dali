#include "Palette.hpp"

Palette::Palette(const ImageArea* imageArea_, QWidget* parent) :
  imageArea(imageArea_),
  QWidget(parent)
{
  // TODO: check that currentImage != nullptr
  const auto palette = imageArea->getCurrentImage()->getPaletteModel()->getPaletteColors();

  const auto numRows = palette.size() / SWATCHES_PER_ROW + 1;
  setFixedSize(SWATCHES_PER_ROW * SWATCH_SIZE + (SWATCHES_PER_ROW - 1) * 2 + 2, numRows * SWATCH_SIZE + (numRows - 1) * 2 + 2);
}

void Palette::paintEvent(QPaintEvent* event)
{
  const auto currentImage = imageArea->getCurrentImage();

  if (!currentImage)
  {
    return;
  }

  const auto palette = currentImage->getPaletteModel()->getPaletteColors();

  QPainter painter(this);

  for (auto i = 0; i < palette.size(); ++i)
  {
    const auto x = i % SWATCHES_PER_ROW;
    const auto y = i / SWATCHES_PER_ROW;

    painter.fillRect(1 + x * SWATCH_SIZE + x * 2, 1 + y * SWATCH_SIZE + y * 2, SWATCH_SIZE, SWATCH_SIZE, palette.at(i));
  }
}