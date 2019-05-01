#include "Tab.hpp"
#include "TabArea.hpp"
#include "SideBar/SideBar.hpp"

Tab::Tab(BrushModel* brushModel, unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  imageArea = std::make_unique<ImageArea>(brushModel, width, height, this);

  const auto rootLayout = new QHBoxLayout();
  rootLayout->addWidget(new SideBar(getImage()->getImageModel(), this));
  rootLayout->addWidget(imageArea.get());
  setLayout(rootLayout);
}