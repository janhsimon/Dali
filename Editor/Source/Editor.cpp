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

  menuBar = std::make_unique<MenuBar>(imageArea.get(), this);
  setMenuBar(menuBar.get());

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