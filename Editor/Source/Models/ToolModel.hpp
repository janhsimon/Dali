#pragma once

#include "BrushModel.hpp"

enum Tool
{
  COLOR_PICKER,
  BRUSH,
  LINE,
  SQUARE,
  CIRCLE,
  FILL
};

class ToolModel : public QObject
{
  Q_OBJECT

public:
  ToolModel();

  BrushModel* getBrushModel() const { return brushModel.get(); }

  Tool getSelectedTool() const { return selectedTool; }
  void setSelectedTool(const Tool tool);

signals:
  void toolChanged(Tool tool);

private:
  // owning
  std::unique_ptr<BrushModel> brushModel;

  Tool selectedTool;
};