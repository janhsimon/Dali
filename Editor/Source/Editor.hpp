#pragma once

#include "MenuBar.hpp"
#include "ToolBar.hpp"

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* parent = nullptr);

private:
  std::unique_ptr<MenuBar> menuBar;
  std::unique_ptr<ToolBar> toolBar;
  std::unique_ptr<TabArea> tabArea;
};
