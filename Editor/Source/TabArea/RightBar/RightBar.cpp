#include "RightBar.hpp"
#include "Layers/Layers.hpp"

RightBar::RightBar(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent)
{
  setFixedWidth(WIDTH);
  
  const auto layout = new QVBoxLayout();
  setLayout(layout);

  layout->addWidget(new Layers(imageModel, this));
  layout->addStretch();
}