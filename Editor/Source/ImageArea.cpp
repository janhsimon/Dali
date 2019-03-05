#include "ImageArea.hpp"

ImageArea::ImageArea(QWidget* parent) :
  QTabWidget(parent)
{
 
}

void ImageArea::newImageTab(const QString& title, unsigned int width, unsigned int height)
{
  setCurrentIndex(addTab(new ImageTab(width, height, this), title));
}

void ImageArea::closeCurrentImageTab()
{
  if (currentIndex() >= 0)
  {
    // TODO: handle confirmation if there are unsaved changes
    // (store a flag 'hasUnsavedChanges' in this class)
    removeTab(currentIndex());
  }
}

void ImageArea::closeAllImageTabs()
{
  // TODO: check if any tabs have any unsaved changes and
  // ask for permission to continue if there are any
  while (currentIndex() >= 0)
  {
    removeTab(currentIndex());
  }
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