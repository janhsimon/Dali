#include "MenuBar.hpp"

MenuBar::MenuBar(MainArea* mainArea_, QWidget* parent) :
  mainArea(mainArea_),
  QMenuBar(parent)
{
  const auto currentImage = mainArea->getCurrentImage();

  const auto fileMenu = addMenu("File");
  fileMenu->addAction("New Project...", [&]() { mainArea->newImageTab("Untitled.dlp", 128u, 128u); }, Qt::Modifier::CTRL + Qt::Key::Key_N);
  fileMenu->addAction("Open Project...");
  const auto openRecentMenu = fileMenu->addMenu("Open Recent Projects");
  openRecentMenu->addAction("PlatformerMockup.dlp");
  openRecentMenu->addAction("DemoProject.dlp");
  fileMenu->addSeparator();
  fileMenu->addAction("Close Project", [&]() { mainArea->closeCurrentImageTab(); }, Qt::Modifier::CTRL + Qt::Key::Key_W);
  fileMenu->addAction("Close All Projects", [&]() { mainArea->closeAllImageTabs(); }, Qt::Modifier::CTRL + Qt::Modifier::SHIFT + Qt::Key::Key_W);
  fileMenu->addSeparator();
  fileMenu->addAction("Save Project");
  fileMenu->addAction("Save Project As...");
  fileMenu->addSeparator();
  fileMenu->addAction("Exit", []() { QApplication::exit(); }, Qt::Modifier::ALT + Qt::Key::Key_F4);

  const auto editMenu = addMenu("Edit");

  const auto viewMenu = addMenu("View");
  
  zoomInAction = viewMenu->addAction("Zoom In", [&]() { const auto currentImage = mainArea->getCurrentImage(); if (currentImage) currentImage->zoomIn(); }, Qt::Key::Key_Plus);
  zoomInAction->setEnabled(currentImage != nullptr);
  
  zoomOutAction = viewMenu->addAction("Zoom Out", [&]() { const auto currentImage = mainArea->getCurrentImage(); if (currentImage) currentImage->zoomOut(); }, Qt::Key::Key_Minus);
  zoomOutAction->setEnabled(currentImage != nullptr);

  viewMenu->addSeparator();

  showGridAction = viewMenu->addAction("Show Grid", [&](bool enabled) { const auto currentImage = mainArea->getCurrentImage(); if (currentImage) currentImage->setDrawGrid(enabled); }, Qt::Key::Key_G);
  showGridAction->setCheckable(true);
  showGridAction->setEnabled(currentImage != nullptr);
  if (currentImage)
  {
    showGridAction->setChecked(currentImage->getDrawGrid());
  }
  
  connect(mainArea, &QTabWidget::currentChanged, this, [&]()
  {
    const auto currentImage = mainArea->getCurrentImage();
    
    zoomInAction->setEnabled(currentImage != nullptr);
    zoomOutAction->setEnabled(currentImage != nullptr);
    showGridAction->setEnabled(currentImage != nullptr);
    
    if (currentImage)
    {
      showGridAction->setChecked(currentImage->getDrawGrid());
    }
  });

  const auto imageMenu = addMenu("Image");
  const auto windowMenu = addMenu("Window");
  const auto helpMenu = addMenu("Help");
}