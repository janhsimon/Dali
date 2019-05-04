#pragma once

#include "Brush.hpp"

class ToolSettingsBar : public QWidget
{
  Q_OBJECT

public:
  ToolSettingsBar(const TabArea* tabArea, QWidget* parent = nullptr);

  BrushModel* getBrushModel() const { return brush->getBrushModel(); }

private:
  std::unique_ptr<Brush> brush;
};