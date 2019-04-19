#include "ToolBar.hpp"

ToolBar::ToolBar(QWidget* parent) :
  QWidget(parent)
{
  setStyleSheet("background-color: #8080FF");
  const auto rootLayout = new QVBoxLayout();
  rootLayout->addWidget(new QPushButton("Pick"));
  rootLayout->addWidget(new QPushButton("Brush"));
  rootLayout->addWidget(new QPushButton("Line"));
  rootLayout->addWidget(new QPushButton("Square"));
  rootLayout->addWidget(new QPushButton("Circle"));
  rootLayout->addWidget(new QPushButton("Fill"));
  rootLayout->addStretch();
  setLayout(rootLayout);
}