#include "ImageArea.hpp"

ImageArea::ImageArea(const BrushModel* brushModel, unsigned int width, unsigned int height, QWidget* parent) :
  QScrollArea(parent)
{
  image = std::make_unique<Image>(brushModel, width, height, this);
  setWidget(image.get());
  setAlignment(Qt::AlignCenter);
}