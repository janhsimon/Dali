#pragma once

#include "MenuBar.hpp"
#include "ToolBar/ToolBar.hpp"

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* parent = nullptr);

private:
  static constexpr auto MIN_WIDTH = 1024;
  static constexpr auto MIN_HEIGHT = 768;

  // memory managed by Qt
  MenuBar* menuBar;
  ToolBar* toolBar;
  TabArea* tabArea;
};
