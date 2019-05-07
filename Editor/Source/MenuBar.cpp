#include "MenuBar.hpp"

MenuBar::MenuBar(TabArea* tabArea, const ToolModel* toolModel, QWidget* parent) :
  QMenuBar(parent),
  tabArea(tabArea),
  toolModel(toolModel)
{
  const auto fileMenu = addMenu("File");
  fileMenu->addAction("New Project...", [&]() { this->tabArea->newImageTab(this->toolModel, "Untitled.dali", 128u, 128u); }, Qt::Modifier::CTRL + Qt::Key::Key_N);

  fileMenu->addAction("Open Project...");
  const auto openRecentMenu = fileMenu->addMenu("Open Recent Projects");
  openRecentMenu->addAction("PlatformerMockup.dali");
  openRecentMenu->addAction("DemoProject.dali");
  fileMenu->addSeparator();
  fileMenu->addAction("Close Project", [&]() { this->tabArea->closeCurrentImageTab(); }, Qt::Modifier::CTRL + Qt::Key::Key_W);
  fileMenu->addAction("Close All Projects", [&]() { this->tabArea->closeAllImageTabs(); }, Qt::Modifier::CTRL + Qt::Modifier::SHIFT + Qt::Key::Key_W);
  fileMenu->addSeparator();
  fileMenu->addAction("Save Project");
  fileMenu->addAction("Save Project As...");
  fileMenu->addSeparator();
  fileMenu->addAction("Exit", []() { QApplication::exit(); }, Qt::Modifier::ALT + Qt::Key::Key_F4);

  const auto editMenu = addMenu("Edit");

  const auto viewMenu = addMenu("View");
  
  const auto currentImage = tabArea->getCurrentImage();

  zoomInAction = viewMenu->addAction("Zoom In", [&]() { if (const auto currentImage = this->tabArea->getCurrentImage(); currentImage) currentImage->zoomIn(); }, Qt::Key::Key_Plus);
  zoomInAction->setEnabled(currentImage != nullptr);
  
  zoomOutAction = viewMenu->addAction("Zoom Out", [&]() { if (const auto currentImage = this->tabArea->getCurrentImage(); currentImage) currentImage->zoomOut(); }, Qt::Key::Key_Minus);
  zoomOutAction->setEnabled(currentImage != nullptr);

  viewMenu->addSeparator();

  showGridAction = viewMenu->addAction("Show Grid", [&](bool enabled) { if (const auto currentImage = this->tabArea->getCurrentImage(); currentImage) currentImage->setDrawGrid(enabled); }, Qt::Key::Key_G);
  showGridAction->setCheckable(true);
  showGridAction->setEnabled(currentImage != nullptr);
  showGridAction->setChecked(currentImage != nullptr && currentImage->getDrawGrid());
  
  connect(tabArea, &QTabWidget::currentChanged, this, [&]()
  {
    const auto currentImage = this->tabArea->getCurrentImage();
    zoomInAction->setEnabled(currentImage != nullptr);
    zoomOutAction->setEnabled(currentImage != nullptr);
    showGridAction->setEnabled(currentImage != nullptr);
    showGridAction->setChecked(currentImage != nullptr && currentImage->getDrawGrid());
  });

  const auto imageMenu = addMenu("Image");
  const auto windowMenu = addMenu("Window");
  const auto helpMenu = addMenu("Help");
}