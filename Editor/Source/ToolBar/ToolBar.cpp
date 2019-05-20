#include "ToolBar.hpp"

ToolBar::ToolBar(const TabArea* tabArea, QWidget* parent) :
  QWidget(parent),
  tabArea(tabArea)
{
  setObjectName("SideBar"); // TODO: change

  const auto layout = new QVBoxLayout();
  setLayout(layout);

  const auto buttonGroup = new QButtonGroup(this);

  colorPickerButton = new ToolButton("Color Picker", QIcon(":/Icons/ColorPicker.svg"), Qt::Key_Q, buttonGroup, this);
  brushButton = new ToolButton("Brush", QIcon(":/Icons/Brush.svg"), Qt::Key_W, buttonGroup, this, true);
  lineButton = new ToolButton("Line", QIcon(":/Icons/Line.svg"), Qt::Key_E, buttonGroup, this);
  squareButton = new ToolButton("Square", QIcon(":/Icons/Square.svg"), Qt::Key_A, buttonGroup, this);
  circleButton = new ToolButton("Circle", QIcon(":/Icons/Circle.svg"), Qt::Key_S, buttonGroup, this);
  fillButton = new ToolButton("Fill", QIcon(":/Icons/Fill.svg"), Qt::Key_D, buttonGroup, this);

  layout->addWidget(colorPickerButton);
  layout->addWidget(brushButton);
  layout->addWidget(lineButton);
  layout->addWidget(squareButton);
  layout->addWidget(circleButton);
  layout->addWidget(fillButton);
  layout->addStretch();
  layout->addWidget(new ToolButton("Settings", QIcon(":/Icons/Settings.svg"), Qt::Key_F, this));

  connect(colorPickerButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::COLOR_PICKER); });
  connect(brushButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::BRUSH); });
  connect(lineButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::LINE); });
  connect(squareButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::SQUARE); });
  connect(circleButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::CIRCLE); });
  connect(fillButton, &QPushButton::clicked, this, [&]() { if (const auto currentToolModel = this->tabArea->getCurrentToolModel(); currentToolModel) currentToolModel->setSelectedTool(Tool::FILL); });
}