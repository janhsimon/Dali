#include "Tab.hpp"
#include "TabArea.hpp"
#include "SideBar/SideBar.hpp"

Tab::Tab(const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  imageArea = std::make_unique<ImageArea>(toolModel, width, height, this);

  const auto rootLayout = new QHBoxLayout();
  rootLayout->addWidget(new SideBar(getImage()->getImageModel(), this));
  rootLayout->addWidget(imageArea.get());
  setLayout(rootLayout);
}