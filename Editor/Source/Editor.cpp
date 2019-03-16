#include "Editor.hpp"
#include "Palette.hpp"
#include "PreviewWindow.hpp"

Editor::Editor(QWidget* parent) :
  QMainWindow(parent)
{
  const auto rootWidget = new QWidget(this);
  const auto rootLayout = new QVBoxLayout();
  rootLayout->setContentsMargins(0, 0, 0, 0);
  
  const auto toolSettingsBar = new QWidget(rootWidget);
  toolSettingsBar->setStyleSheet("background-color: #FF8080");
  toolSettingsBar->setMinimumHeight(64);
  const auto toolSettingsBarLayout = new QHBoxLayout();
  toolSettingsBarLayout->addWidget(new QLabel("Tool-specific settings go here..."));
  toolSettingsBar->setLayout(toolSettingsBarLayout);
  rootLayout->addWidget(toolSettingsBar);

  const auto mainLayout = new QHBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);

  const auto toolBar = new QWidget(rootWidget);
  toolBar->setStyleSheet("background-color: #8080FF");
  const auto toolBarLayout = new QVBoxLayout();
  toolBarLayout->addWidget(new QPushButton("Pick"));
  toolBarLayout->addWidget(new QPushButton("Brush"));
  toolBarLayout->addWidget(new QPushButton("Line"));
  toolBarLayout->addWidget(new QPushButton("Square"));
  toolBarLayout->addWidget(new QPushButton("Circle"));
  toolBarLayout->addWidget(new QPushButton("Fill"));
  toolBarLayout->addStretch();
  toolBar->setLayout(toolBarLayout);
  mainLayout->addWidget(toolBar);

  mainArea = std::make_unique<MainArea>(this);
  mainLayout->addWidget(mainArea.get());

  rootLayout->addLayout(mainLayout);
  
  const auto statusBar = new QStatusBar(this);
  statusBar->addWidget(new QLabel("This is the status bar."));
  statusBar->setMinimumHeight(24);
  statusBar->setStyleSheet("background-color: #0880FF");
  setStatusBar(statusBar);

  rootWidget->setLayout(rootLayout);
  setCentralWidget(rootWidget);

  menuBar = std::make_unique<MenuBar>(mainArea.get(), this);
  setMenuBar(menuBar.get());

  const auto previewWindow = new PreviewWindow(mainArea.get(), this);
  previewWindow->show();
  //previewWindow->move(QPoint(pos().x() /*- previewWindow->frameGeometry().width()*/, pos().y() /*- previewWindow->frameGeometry().height()*/));
}

int main(int argc, char* argv[])
{
  QApplication application(argc, argv);

  Editor editor;
  editor.showMaximized();

  return application.exec();
}