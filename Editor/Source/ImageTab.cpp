#include "ImageTab.hpp"
#include "Layers.hpp"
#include "MainArea.hpp"
#include "Palette.hpp"

ImageTab::ImageTab(unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  imageScrollArea = std::make_unique<ImageScrollArea>(width, height, this);

  const auto rootLayout = new QHBoxLayout();

  const auto sideBar = new QWidget();
  sideBar->setStyleSheet("background-color: #80FF80");
  sideBar->setFixedWidth(200);
  const auto sideBarLayout = new QVBoxLayout();
  sideBarLayout->setContentsMargins(0, 0, 0, 0);
  sideBarLayout->addWidget(new Palette(imageScrollArea->getImage()->getImageModel(), this));
  sideBarLayout->addWidget(new Layers(imageScrollArea->getImage()->getImageModel(), this));
  sideBarLayout->addStretch();
  sideBar->setLayout(sideBarLayout);
  rootLayout->addWidget(sideBar);

  rootLayout->addWidget(imageScrollArea.get());

  setLayout(rootLayout);
}