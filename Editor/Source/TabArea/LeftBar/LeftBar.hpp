#pragma once

#include "Palette.hpp"
#include "ToolSettings/ToolSettings.hpp"
#include "../../Models/ImageModel.hpp"

class LeftBar : public QWidget
{
  Q_OBJECT

public:
  LeftBar(ImageModel* imageModel, const ToolModel* toolModel, QWidget* parent = nullptr);

private:
  static constexpr auto WIDTH = 150;

  // memory managed by Qt
  Palette* palette;
  ToolSettings* toolSettings;
};