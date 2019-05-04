#include "Editor.hpp"
#include "PreviewWindow.hpp"
#include "Models/BrushModel.hpp"
#include "TabArea/TabArea.hpp"

Editor::Editor(QWidget* parent) :
  QMainWindow(parent)
{
  const auto rootWidget = new QWidget(this);

  tabArea = std::make_unique<TabArea>(this);
  toolSettingsBar = std::make_unique<ToolSettingsBar>(tabArea.get(), rootWidget);
  menuBar = std::make_unique<MenuBar>(tabArea.get(), toolSettingsBar->getBrushModel(), this);

  const auto rootLayout = new QVBoxLayout();
  rootLayout->setContentsMargins(0, 0, 0, 0);
  
  rootLayout->addWidget(toolSettingsBar.get());

  const auto mainLayout = new QHBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(new ToolBar(rootWidget));
  mainLayout->addWidget(tabArea.get());
  rootLayout->addLayout(mainLayout);
  
  const auto statusBar = new QStatusBar(this);
  statusBar->addWidget(new QLabel("This is the status bar."));
  statusBar->setMinimumHeight(24);
  statusBar->setStyleSheet("background-color: #0880FF");
  setStatusBar(statusBar);

  rootWidget->setLayout(rootLayout);
  setCentralWidget(rootWidget);

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