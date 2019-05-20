#include "ToolSettings.hpp"

ToolSettings::ToolSettings(const ToolModel* toolModel, QWidget* parent) :
  QStackedWidget(parent)
{
  {
    const auto colorPickerWidget = new QWidget(this);
    addWidget(colorPickerWidget);
    
    const auto colorPickerLayout = new QVBoxLayout();
    colorPickerWidget->setLayout(colorPickerLayout);

    colorPickerLayout->addWidget(new QLabel("Color picker tool settings", colorPickerWidget));
    colorPickerLayout->addStretch();
  }

  {
    const auto brushWidget = new QWidget(this);
    addWidget(brushWidget);

    const auto brushLayout = new QVBoxLayout();  
    brushWidget->setLayout(brushLayout);
    
    brush = new Brush(toolModel->getBrushModel(), brushWidget);
    brushLayout->addWidget(brush);
    brushLayout->addWidget(new QLabel("More brush tool settings", brushWidget));
    brushLayout->addStretch();
  }

  {
    const auto lineWidget = new QWidget(this);
    addWidget(lineWidget);

    const auto lineLayout = new QVBoxLayout();
    lineWidget->setLayout(lineLayout);

    lineLayout->addWidget(new QLabel("Line tool settings", lineWidget));
    lineLayout->addStretch();
  }

  {
    const auto squareWidget = new QWidget(this);
    addWidget(squareWidget);

    const auto squareLayout = new QVBoxLayout();
    squareWidget->setLayout(squareLayout);

    squareLayout->addWidget(new QLabel("Square tool settings", squareWidget));
    squareLayout->addStretch();
  }

  {
    const auto circleWidget = new QWidget(this);
    addWidget(circleWidget);

    const auto circleLayout = new QVBoxLayout();
    circleWidget->setLayout(circleLayout);

    circleLayout->addWidget(new QLabel("Circle tool settings", circleWidget));
    circleLayout->addStretch();
  }

  {
    const auto fillWidget = new QWidget(this);
    addWidget(fillWidget);

    const auto fillLayout = new QVBoxLayout();
    fillWidget->setLayout(fillLayout);

    fillLayout->addWidget(new QLabel("Fill tool settings", fillWidget));
    fillLayout->addStretch();
  }

  setCurrentIndex(static_cast<int>(toolModel->getSelectedTool()));

  connect(toolModel, &ToolModel::toolChanged, this, [&](Tool tool) { setCurrentIndex(static_cast<int>(tool)); });
}