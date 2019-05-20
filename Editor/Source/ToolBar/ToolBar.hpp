#pragma once

#include "ToolButton.hpp"
#include "../TabArea/TabArea.hpp"

class ToolBar : public QWidget
{
  Q_OBJECT

public:
  ToolBar(const TabArea* tabArea, QWidget* parent = nullptr);

private:
  // non-owning
  const TabArea* tabArea;

  // memory managed by Qt
  ToolButton* colorPickerButton;
  ToolButton* brushButton;
  ToolButton* lineButton;
  ToolButton* squareButton;
  ToolButton* circleButton;
  ToolButton* fillButton;
};