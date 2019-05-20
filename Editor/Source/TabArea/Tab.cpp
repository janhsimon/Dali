#include "Tab.hpp"
#include "TabArea.hpp"

Tab::Tab(unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  toolModel = std::make_unique<ToolModel>();
  imageModel = std::make_unique<ImageModel>(toolModel.get(), width, height);
  
  imageArea = new ImageArea(imageModel.get(), toolModel.get(), width, height, this);
  leftBar = new LeftBar(imageModel.get(), toolModel.get(), this);
  rightBar = new RightBar(imageModel.get(), this);

  const auto layout = new QHBoxLayout();
  setLayout(layout);

  layout->addWidget(leftBar);
  layout->addWidget(imageArea);
  layout->addWidget(rightBar);
}