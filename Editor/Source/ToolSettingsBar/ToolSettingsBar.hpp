#pragma once

#include "Brush.hpp"
#include "../Models/ToolModel.hpp"

class ToolSettingsBar : public QStackedWidget
{
  Q_OBJECT

public:
  ToolSettingsBar(const TabArea* tabArea, QWidget* parent = nullptr);

  ToolModel* getToolModel() const { return toolModel.get(); }

private:
  std::unique_ptr<ToolModel> toolModel;
  std::unique_ptr<Brush> brush;
};