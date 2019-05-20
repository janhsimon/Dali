#pragma once

#include "Brush.hpp"
#include "../../../Models/ToolModel.hpp"

class ToolSettings : public QStackedWidget
{
  Q_OBJECT

public:
  ToolSettings(const ToolModel* toolModel, QWidget* parent = nullptr);

private:
  // memory managed by Qt
  Brush *brush;
};