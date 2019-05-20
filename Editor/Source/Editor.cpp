#include "Editor.hpp"
#include "PreviewWindow.hpp"
#include "Models/BrushModel.hpp"
#include "TabArea/TabArea.hpp"

Editor::Editor(QWidget* parent) :
  QMainWindow(parent)
{
  const auto widget = new QWidget(this);
  setCentralWidget(widget);

  const auto layout = new QHBoxLayout();
  widget->setLayout(layout);

  tabArea = new TabArea(widget);
  menuBar = new MenuBar(tabArea, this);
  toolBar = new ToolBar(tabArea, widget);
  
  setMenuBar(menuBar);

  layout->addWidget(toolBar);
  layout->addWidget(tabArea);
  
  {
    const auto statusBar = new QStatusBar(this);
    statusBar->addWidget(new QLabel("Image size and mouse position could go here."));
    statusBar->addWidget(new QLabel("And the current zoom level and a slider maybe."));
    statusBar->setFixedHeight(24);
    setStatusBar(statusBar);
  }

  const auto previewWindow = new PreviewWindow(tabArea, this);
  //previewWindow->move(QPoint(pos().x() /*- previewWindow->frameGeometry().width()*/, pos().y() /*- previewWindow->frameGeometry().height()*/));
  //previewWindow->setGeometry(x(), y() + height() - previewWindow->height(), previewWindow->width(), previewWindow->height());
  //previewWindow->show();

  setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
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