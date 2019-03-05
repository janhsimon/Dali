#pragma once

#include "ImageArea.hpp"

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(ImageArea* imageArea, QWidget* parent = nullptr);

private:
  ImageArea* imageArea;

  QAction* zoomInAction;
  QAction* zoomOutAction;
  QAction* showGridAction;
};