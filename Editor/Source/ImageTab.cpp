#include "ImageTab.hpp"

ImageTab::ImageTab(QWidget* parent) :
  QScrollArea(parent)
{
  image = std::make_unique<Image>(128, 128, this);
  setWidget(image.get());
  setAlignment(Qt::AlignCenter);
}