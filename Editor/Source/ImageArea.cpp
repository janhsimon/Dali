#include "ImageArea.hpp"

ImageArea::ImageArea(QWidget* parent) :
  QTabWidget(parent)
{
  addTab(new ImageTab(parent), "PlatformerMockup.dlp");
  addTab(new ImageTab(parent), "DemoProject.dlp");
}

Image* ImageArea::getCurrentImage() const
{
  const auto currentImageTab = static_cast<ImageTab*>(currentWidget());

  if (!currentImageTab)
  {
    return nullptr;
  }
  
  return currentImageTab->getImage();
}