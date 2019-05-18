#include "LayerList.hpp"

LayerList::LayerList(ImageModel* imageModel, QWidget* parent) :
  QListWidget(parent),
  imageModel(imageModel)
{
  setDragDropMode(QAbstractItemView::InternalMove); // allow re-ordering of list via drag-and-drop

  connect(this, &QListWidget::currentRowChanged, this, [&](int currentRow) { this->imageModel->setSelectedLayerIndex(currentRow); });
  
  connect(model(), &QAbstractItemModel::rowsMoved, this, [&](const QModelIndex&, int from, int, const QModelIndex&, int to)
  {
    this->imageModel->changeLayerOrder(from, to);

    // make sure to update the selected layer index of the model after changing the layer order
    this->imageModel->setSelectedLayerIndex(currentRow());
  });
}

void LayerList::addLayer(const QString& layerName)
{
  const auto listItem = new QListWidgetItem(this);
  const auto itemWidget = new LayerListItem(layerName, imageModel, this);
  setItemWidget(listItem, itemWidget);
  listItem->setSizeHint(itemWidget->minimumSizeHint());
  addItem(listItem);
}