#include "ToolSettingsBar.hpp"

ToolSettingsBar::ToolSettingsBar(const TabArea* tabArea, QWidget* parent) :
  QStackedWidget(parent)
{
  toolModel = std::make_unique<ToolModel>();

  {
    const auto colorPickerWidget = new QWidget(this);
    const auto colorPickerLayout = new QHBoxLayout();
    colorPickerLayout->addWidget(new QLabel("These are the tool settings for the color picker tool...", colorPickerWidget));
    colorPickerLayout->addStretch();
    colorPickerWidget->setLayout(colorPickerLayout);
    addWidget(colorPickerWidget);
  }

  {
    const auto brushWidget = new QWidget(this);
    const auto brushLayout = new QHBoxLayout();
    brush = std::make_unique<Brush>(tabArea, toolModel->getBrushModel(), brushWidget);
    brushLayout->addWidget(brush.get());
    brushLayout->addWidget(new QLabel("And these are some more tool settings for the brush tool...", brushWidget));
    brushLayout->addStretch();
    brushWidget->setLayout(brushLayout);
    addWidget(brushWidget);
  }

  {
    const auto lineWidget = new QWidget(this);
    const auto lineLayout = new QHBoxLayout();
    lineLayout->addWidget(new QLabel("These are the tool settings for the line tool...", lineWidget));
    lineLayout->addStretch();
    lineWidget->setLayout(lineLayout);
    addWidget(lineWidget);
  }

  {
    const auto squareWidget = new QWidget(this);
    const auto squareLayout = new QHBoxLayout();
    squareLayout->addWidget(new QLabel("These are the tool settings for the square tool...", squareWidget));
    squareLayout->addStretch();
    squareWidget->setLayout(squareLayout);
    addWidget(squareWidget);
  }

  {
    const auto circleWidget = new QWidget(this);
    const auto circleLayout = new QHBoxLayout();
    circleLayout->addWidget(new QLabel("These are the tool settings for the circle tool...", circleWidget));
    circleLayout->addStretch();
    circleWidget->setLayout(circleLayout);
    addWidget(circleWidget);
  }

  {
    const auto fillWidget = new QWidget(this);
    const auto fillLayout = new QHBoxLayout();
    fillLayout->addWidget(new QLabel("These are the tool settings for the fill tool...", fillWidget));
    fillLayout->addStretch();
    fillWidget->setLayout(fillLayout);
    addWidget(fillWidget);
  }

  setCurrentIndex(static_cast<int>(toolModel->getSelectedTool()));

  setFixedHeight(128);

  connect(toolModel.get(), &ToolModel::toolChanged, this, [&](Tool tool) { setCurrentIndex(static_cast<int>(tool)); });
}