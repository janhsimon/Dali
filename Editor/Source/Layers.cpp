#include "Layers.hpp"

Layers::Layers(ImageModel* imageModel, QWidget* parent) :
  imageModel(imageModel),
  QWidget(parent)
{
  setStyleSheet("background-color: #FF0080");

  const auto rootLayout = new QGridLayout();
  rootLayout->setContentsMargins(0, 0, 0, 0);

  layerList = std::make_unique<QListWidget>(this);
  layerList->addItem("Layer 1");
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

  connect(layerList.get(), &QListWidget::currentRowChanged, this, [&](int currentRow) { this->imageModel->setSelectedLayerIndex(currentRow); });
  connect(addLayerButton, &QPushButton::clicked, this, [&]() { this->imageModel->addLayer(); layerList->addItem("New Layer"); });
  connect(removeLayerButton, &QPushButton::clicked, this, [&]() { this->imageModel->removeSelectedLayer(); });
}