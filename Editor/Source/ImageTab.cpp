#include "ImageTab.hpp"

ImageTab::ImageTab(unsigned int width, unsigned int height, QWidget* parent) :
  QScrollArea(parent)
{
  image = std::make_unique<Image>(width, height, this);
  setWidget(image.get());
  setAlignment(Qt::AlignCenter);
}