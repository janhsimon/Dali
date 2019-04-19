#pragma once

#include "TabArea/TabArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(TabArea* tabArea, QWidget* parent = nullptr);

private:
  TabArea* tabArea;

  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};