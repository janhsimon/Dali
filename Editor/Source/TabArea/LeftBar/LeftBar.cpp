#include "LeftBar.hpp"

LeftBar::LeftBar(ImageModel* imageModel, const ToolModel* toolModel, QWidget* parent) :
  QWidget(parent)
{
  setFixedWidth(WIDTH);
  
  palette = new Palette(imageModel, this);
  toolSettings = new ToolSettings(toolModel, this);

  const auto layout = new QVBoxLayout();
  setLayout(layout);

  layout->addWidget(palette);
  layout->addWidget(toolSettings);
  layout->addStretch();
}