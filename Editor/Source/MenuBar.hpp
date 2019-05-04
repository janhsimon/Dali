#pragma once

#include "TabArea/TabArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(TabArea* tabArea, BrushModel* brushModel, QWidget* parent = nullptr);

private:
  TabArea* tabArea;
  BrushModel* brushModel;

  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};