#pragma once

#include "TabArea/TabArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(TabArea* tabArea, QWidget* parent = nullptr);

private:
  // non-owning
  TabArea* tabArea;

  // memory managed by Qt
  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};