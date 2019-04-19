#include "Tab.hpp"
#include "TabArea.hpp"
#include "SideBar/SideBar.hpp"

Tab::Tab(unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  imageScrollArea = std::make_unique<ImageScrollArea>(width, height, this);

  const auto rootLayout = new QHBoxLayout();
  rootLayout->addWidget(new SideBar(getImage()->getImageModel(), this));
  rootLayout->addWidget(imageScrollArea.get());
  setLayout(rootLayout);
}