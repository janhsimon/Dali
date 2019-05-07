#pragma once

#include "TabArea/TabArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(TabArea* tabArea, const ToolModel* toolModel, QWidget* parent = nullptr);

private:
  TabArea* tabArea;
  const ToolModel* toolModel;

  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};