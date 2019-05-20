#include "Layers.hpp"

Layers::Layers(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent),
  imageModel(imageModel)
{
  layerList = new LayerList(imageModel, this);
  layerList->addLayer("Layer 1");

  const auto buttonBar = new QWidget(this);

  const auto buttonBarLayout = new QVBoxLayout();
  buttonBar->setLayout(buttonBarLayout);

  addLayerButton = new QPushButton("+", this);
  addLayerButton->setFixedSize(32, 32);
  
  removeLayerButton = new QPushButton("-", this);
  removeLayerButton->setFixedSize(32, 32);

  buttonBarLayout->addWidget(addLayerButton);
  buttonBarLayout->addWidget(removeLayerButton);
  buttonBarLayout->addStretch();
  
  const auto backgroundColorButton = new QPushButton("...");
  backgroundColorButton->setFixedSize(32, 32);

  const auto layout = new QGridLayout();
  setLayout(layout);

  layout->setContentsMargins(2, 2, 2, 2);
  layout->addWidget(layerList, 0, 0);
  layout->addWidget(buttonBar, 0, 1);
  layout->addWidget(new QLabel("Background color:", this), 1, 0);
  layout->addWidget(backgroundColorButton, 1, 1);
  
  connect(addLayerButton, &QPushButton::clicked, this, [&]()
  {
    this->imageModel->addLayer();
    layerList->addLayer("Layer " + QString::number(layerList->count() + 1));
    
    layerList->setItemSelected(layerList->item(layerList->count() - 1), true);
  });
  
  connect(removeLayerButton, &QPushButton::clicked, this, [&]()
  {
    if (this->imageModel->getLayerCount() <= 1)
    {
      return;
    }

    this->imageModel->removeSelectedLayer();
    layerList->takeItem(this->imageModel->getSelectedLayerIndex());
    this->imageModel->setSelectedLayerIndex(/*this->imageModel->getSelectedLayerIndex() - 1*/0);
    layerList->setItemSelected(layerList->item(0), true);
  });
}