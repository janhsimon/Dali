#include "ToolSettingsBar.hpp"

ToolSettingsBar::ToolSettingsBar(QWidget* parent) :
  QWidget(parent)
{
  setStyleSheet("background-color: #FF8080");

  const auto rootLayout = new QHBoxLayout();

  brush = std::make_unique<Brush>(this);
  rootLayout->addWidget(brush.get());
  rootLayout->addStretch();
  
  setLayout(rootLayout);
}