#pragma once

#include "ToolButton.hpp"
#include "../TabArea/TabArea.hpp"
#include "../Models/ToolModel.hpp"

class ToolBar : public QWidget
{
  Q_OBJECT

public:
  ToolBar(ToolModel* toolModel, QWidget* parent = nullptr);

private:
  ToolModel* toolModel;
  std::unique_ptr<ToolButton> colorPickerButton, brushButton, lineButton, squareButton, circleButton, fillButton;
};