#pragma once

#include "MainArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(MainArea* mainArea, QWidget* parent = nullptr);

private:
  MainArea* mainArea;

  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};