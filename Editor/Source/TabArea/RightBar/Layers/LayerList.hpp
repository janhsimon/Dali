#pragma once

#include "LayerListItem.hpp"

class LayerList : public QListWidget
{
  Q_OBJECT

public:
  LayerList(ImageModel* imageModel, QWidget* parent = nullptr);

  void addLayer(const QString& layerName);

private:
  ImageModel* imageModel;
};