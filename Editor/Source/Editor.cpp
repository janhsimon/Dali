#include "Editor.hpp"
#include "TabArea/Sidebar/Palette.hpp"
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

  mainLayout->addWidget(new ToolBar(rootWidget));

  tabArea = std::make_unique<TabArea>(this);
  mainLayout->addWidget(tabArea.get());

  rootLayout->addLayout(mainLayout);
  
  const auto statusBar = new QStatusBar(this);
  statusBar->addWidget(new QLabel("This is the status bar."));
  statusBar->setMinimumHeight(24);
  statusBar->setStyleSheet("background-color: #0880FF");
  setStatusBar(statusBar);

  rootWidget->setLayout(rootLayout);
  setCentralWidget(rootWidget);

  menuBar = std::make_unique<MenuBar>(tabArea.get(), this);
  setMenuBar(menuBar.get());

  const auto previewWindow = new PreviewWindow(tabArea.get(), this);
  //previewWindow->move(QPoint(pos().x() /*- previewWindow->frameGeometry().width()*/, pos().y() /*- previewWindow->frameGeometry().height()*/));
  //previewWindow->setGeometry(x(), y() + height() - previewWindow->height(), previewWindow->width(), previewWindow->height());
  previewWindow->show();

  setMinimumSize(1024, 768);
}

int main(int argc, char* argv[])
{
  QApplication application(argc, argv);

  Editor editor;
  editor.show/*Maximized*/();

  return application.exec();
}