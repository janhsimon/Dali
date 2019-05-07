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
  menuBar = std::make_unique<MenuBar>(tabArea.get(), toolSettingsBar->getToolModel(), this);

  const auto rootLayout = new QVBoxLayout();
  
  rootLayout->addWidget(toolSettingsBar.get());

  const auto mainLayout = new QHBoxLayout();
  mainLayout->addWidget(new ToolBar(toolSettingsBar->getToolModel(), rootWidget));
  mainLayout->addWidget(tabArea.get());
  rootLayout->addLayout(mainLayout);
  
  const auto statusBar = new QStatusBar(this);
  statusBar->addWidget(new QLabel("This is the status bar."));
  statusBar->addWidget(new QLabel("And this is a second element."));
  statusBar->setMinimumHeight(24);
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

QString mergeStylesheets(const QString& directory)
{
  QByteArray mergedStylesheet;

  const auto filenames = QDir(directory).entryList(QStringList() << "*.css", QDir::Files);
  for (const auto& filename : filenames)
  {
    QFile stylesheet(directory + "/" + filename);
    if (stylesheet.open(QFile::ReadOnly))
    {
      mergedStylesheet += stylesheet.readAll();
    }
  }

  return QLatin1String(mergedStylesheet);
}

int main(int argc, char* argv[])
{
  QApplication application(argc, argv);
  application.setStyleSheet(mergeStylesheets(":/Styles"));

  Editor editor;
  editor.show/*Maximized*/();
  return application.exec();
}