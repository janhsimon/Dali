#include "Layers.hpp"

Layers::Layers(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent),
  imageModel(imageModel)
{
  const auto rootLayout = new QGridLayout();

  layerList = std::make_unique<QListWidget>(this);
  layerList->addItem("Layer 1");
  layerList->setDragDropMode(QAbstractItemView::InternalMove); // allow re-ordering of list via drag-and-drop
  layerList->setEditTriggers(layerList->editTriggers() | QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed); // allow renaming of list items
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
  
  connect(layerList.get()->model(), &QAbstractItemModel::rowsMoved, this, [&](const QModelIndex&, int from, int, const QModelIndex&, int to)
  {
    this->imageModel->changeLayerOrder(from, to);

    // make sure to update the selected layer index of the model after changing the layer order
    this->imageModel->setSelectedLayerIndex(layerList->currentRow());
  });
  
  connect(addLayerButton, &QPushButton::clicked, this, [&]()
  {
    this->imageModel->addLayer();
    layerList->addItem("Layer " + QString::number(layerList->count() + 1));
    
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