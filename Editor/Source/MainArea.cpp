#include "MainArea.hpp"

MainArea::MainArea(QWidget* parent) :
  QTabWidget(parent)
{
 
}

void MainArea::newImageTab(const QString& title, unsigned int width, unsigned int height)
{
  setCurrentIndex(addTab(new ImageTab(width, height, this), title));
}

void MainArea::closeCurrentImageTab()
{
  if (currentIndex() >= 0)
  {
    // TODO: handle confirmation if there are unsaved changes
    // (store a flag 'hasUnsavedChanges' in this class)
    removeTab(currentIndex());
  }
}

void MainArea::closeAllImageTabs()
{
  // TODO: check if any tabs have any unsaved changes and
  // ask for permission to continue if there are any
  while (currentIndex() >= 0)
  {
    removeTab(currentIndex());
  }
}

Image* MainArea::getCurrentImage() const
{
  const auto currentImageTab = static_cast<ImageTab*>(currentWidget());

  if (!currentImageTab)
  {
    return nullptr;
  }
  
  return currentImageTab->getImage();
}