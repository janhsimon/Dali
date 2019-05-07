#include "Layers.hpp"
#include "Palette.hpp"
#include "SideBar.hpp"

SideBar::SideBar(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent)
{
  setFixedWidth(200);
  
  const auto rootLayout = new QVBoxLayout();
  rootLayout->addWidget(new Palette(imageModel, this));
  rootLayout->addWidget(new Layers(imageModel, this));
  rootLayout->addStretch();
  setLayout(rootLayout);
}