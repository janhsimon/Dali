#pragma once

#include "ToolModel.hpp"

ToolModel::ToolModel()
{
  brushModel = std::make_unique<BrushModel>();
  setSelectedTool(Tool::BRUSH);
}

void ToolModel::setSelectedTool(const Tool tool)
{
  selectedTool = tool;
  emit toolChanged(selectedTool);
}