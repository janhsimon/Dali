#include "TabArea.hpp"

TabArea::TabArea(QWidget* parent) :
  QTabWidget(parent)
{
}

void TabArea::newImageTab(const QString& title, unsigned int width, unsigned int height)
{
  setCurrentIndex(addTab(new Tab(width, height, this), title));
}

void TabArea::closeCurrentImageTab()
{
  if (currentIndex() >= 0)
  {
    // TODO: handle confirmation if there are unsaved changes
    // (store a flag 'hasUnsavedChanges' in this class)
    removeTab(currentIndex());
  }
}

void TabArea::closeAllImageTabs()
{
  // TODO: check if any tabs have any unsaved changes and
  // ask for permission to continue if there are any
  while (currentIndex() >= 0)
  {
    removeTab(currentIndex());
  }
}

Image* TabArea::getCurrentImage() const
{
  if (const auto currentTab = currentWidget(); currentTab)
  {
    return static_cast<Tab*>(currentTab)->getImage();
  }

  return nullptr;
}

ImageModel* TabArea::getCurrentImageModel() const
{
  if (const auto currentTab = currentWidget(); currentTab)
  {
    return static_cast<Tab*>(currentTab)->getImageModel();
  }

  return nullptr;
}

ToolModel* TabArea::getCurrentToolModel() const
{
  if (const auto currentTab = currentWidget(); currentTab)
  {
    return static_cast<Tab*>(currentTab)->getToolModel();
  }

  return nullptr;
}