#include "ImageArea.hpp"

ImageArea::ImageArea(const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent) :
  QScrollArea(parent)
{
  setObjectName("ImageArea");

  image = std::make_unique<Image>(toolModel, width, height, this);
  setWidget(image.get());
  setAlignment(Qt::AlignCenter);
}