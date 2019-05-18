#include "Layers.hpp"

Layers::Layers(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent),
  imageModel(imageModel)
{
  const auto rootLayout = new QGridLayout();
  rootLayout->setContentsMargins(2, 2, 2, 2);

  layerList = std::make_unique<LayerList>(imageModel, this);
  layerList->addLayer("Layer 1");
  rootLayout->addWidget(layerList.get(), 0, 0);

  const auto buttonBar = new QWidget(this);
  const auto buttonBarLayout = new QVBoxLayout();

  addLayerButton = new QPushButton("+", this);
  addLayerButton->setFixedSize(32, 32);
  buttonBarLayout->addWidget(addLayerButton);

  removeLayerButton = new QPushButton("-", this);
  removeLayerButton->setFixedSize(32, 32);
  buttonBarLayout->addWidget(removeLayerButton);

  buttonBarLayout->addStretch();
  buttonBar->setLayout(buttonBarLayout);
  rootLayout->addWidget(buttonBar, 0, 1);

  rootLayout->addWidget(new QLabel("Background color:", this), 1, 0);

  const auto backgroundColorButton = new QPushButton("...");
  backgroundColorButton->setFixedSize(32, 32);
  rootLayout->addWidget(backgroundColorButton, 1, 1);

  setLayout(rootLayout);
  
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