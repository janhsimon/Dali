#include "ImageArea.hpp"

ImageArea::ImageArea(ImageModel* imageModel, const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent) :
  QScrollArea(parent)
{
  setObjectName("ImageArea");

  image = new Image(imageModel, toolModel, width, height, this);
  setWidget(image);
  setAlignment(Qt::AlignCenter);
}