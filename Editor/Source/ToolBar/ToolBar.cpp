#include "ToolBar.hpp"

ToolBar::ToolBar(ToolModel* toolModel, QWidget* parent) :
  QWidget(parent),
  toolModel(toolModel)
{
  setObjectName("SideBar");

  const auto rootLayout = new QVBoxLayout();
  const auto buttonGroup = new QButtonGroup(this);

  colorPickerButton = std::make_unique<ToolButton>("Color Picker", QIcon(":/Icons/ColorPicker.svg"), Qt::Key_Q, buttonGroup, this);
  rootLayout->addWidget(colorPickerButton.get());

  brushButton = std::make_unique<ToolButton>("Brush", QIcon(":/Icons/Brush.svg"), Qt::Key_W, buttonGroup, this, true);
  rootLayout->addWidget(brushButton.get());

  lineButton = std::make_unique<ToolButton>("Line", QIcon(":/Icons/Line.svg"), Qt::Key_E, buttonGroup, this);
  rootLayout->addWidget(lineButton.get());

  squareButton = std::make_unique<ToolButton>("Square", QIcon(":/Icons/Square.svg"), Qt::Key_A, buttonGroup, this);
  rootLayout->addWidget(squareButton.get());

  circleButton = std::make_unique<ToolButton>("Circle", QIcon(":/Icons/Circle.svg"), Qt::Key_S, buttonGroup, this);
  rootLayout->addWidget(circleButton.get());

  fillButton = std::make_unique<ToolButton>("Fill", QIcon(":/Icons/Fill.svg"), Qt::Key_D, buttonGroup, this);
  rootLayout->addWidget(fillButton.get());

  rootLayout->addStretch();

  rootLayout->addWidget(new ToolButton("Settings", QIcon(":/Icons/Settings.svg"), Qt::Key_F, this));

  setLayout(rootLayout);

  connect(colorPickerButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::COLOR_PICKER); });
  connect(brushButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::BRUSH); });
  connect(lineButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::LINE); });
  connect(squareButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::SQUARE); });
  connect(circleButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::CIRCLE); });
  connect(fillButton.get(), &QPushButton::clicked, this, [&]() { this->toolModel->setSelectedTool(Tool::FILL); });
}