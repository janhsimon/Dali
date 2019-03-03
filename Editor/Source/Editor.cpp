#include "Editor.hpp"
#include "Palette.hpp"

Editor::Editor(QWidget* parent) :
  QMainWindow(parent)
{
  const auto rootWidget = new QWidget(this);
  const auto rootLayout = new QVBoxLayout();
  rootLayout->setContentsMargins(0, 0, 0, 0);
  
  const auto toolBar = new QWidget(rootWidget);
  toolBar->setMinimumHeight(48);
  toolBar->setStyleSheet("background-color: #0808FF");
  rootLayout->addWidget(toolBar);

  imageArea = std::make_unique<ImageArea>(this);

  const auto mainLayout = new QHBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  const auto sideBar = new QWidget(rootWidget);
  sideBar->setStyleSheet("background-color: #FF0808");
  const auto sideBarLayout = new QVBoxLayout();
  sideBarLayout->addWidget(new Palette(imageArea.get()));
  sideBarLayout->addStretch();
  sideBar->setLayout(sideBarLayout);
  mainLayout->addWidget(sideBar);
  mainLayout->addWidget(imageArea.get());
  rootLayout->addLayout(mainLayout);
  
  const auto statusBar = new QWidget(rootWidget);
  statusBar->setMinimumHeight(24);
  statusBar->setStyleSheet("background-color: #FEBB08");
  rootLayout->addWidget(statusBar);

  rootWidget->setLayout(rootLayout);
  setCentralWidget(rootWidget);

  const auto menuBar = new QMenuBar();

  const auto fileMenu = menuBar->addMenu("File");
  fileMenu->addAction("New Project...");
  fileMenu->addAction("Open Project...");
  const auto openRecentMenu = fileMenu->addMenu("Open Recent Projects");
  openRecentMenu->addAction("PlatformerMockup.dlp");
  openRecentMenu->addAction("DemoProject.dlp");
  fileMenu->addSeparator();
  fileMenu->addAction("Save Project");
  fileMenu->addAction("Save Project As...");
  fileMenu->addSeparator();
  fileMenu->addAction("Exit");
  setMenuBar(menuBar);

  const auto editMenu = menuBar->addMenu("Edit");

  const auto viewMenu = menuBar->addMenu("View");
  const auto zoomInAction = viewMenu->addAction("Zoom In", [&]() { imageArea->getCurrentImage()->zoomIn(); }, Qt::Key::Key_Plus);
  const auto zoomOutAction = viewMenu->addAction("Zoom Out", [&]() { imageArea->getCurrentImage()->zoomOut(); }, Qt::Key::Key_Minus);
  viewMenu->addSeparator();
  const auto showGridAction = viewMenu->addAction("Show Grid", [&](bool enabled) { imageArea->getCurrentImage()->setDrawGrid(enabled); }, Qt::Key::Key_G);
  showGridAction->setCheckable(true);
  showGridAction->setChecked(imageArea->getCurrentImage()->getDrawGrid());

  const auto imageMenu = menuBar->addMenu("Image");
  const auto windowMenu = menuBar->addMenu("Window");
  const auto helpMenu = menuBar->addMenu("Help");

  const auto previewWindow = new QWidget(this);
  previewWindow->setMinimumSize(320, 200);
  previewWindow->setWindowTitle("Preview");
  previewWindow->setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
  previewWindow->show();
}

int main(int argc, char* argv[])
{
  QApplication application(argc, argv);

  Editor editor;
  editor.showMaximized();

  return application.exec();
}