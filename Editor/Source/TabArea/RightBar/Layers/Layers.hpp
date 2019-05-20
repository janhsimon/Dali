#pragma once

#include "LayerList.hpp"

class Layers : public QWidget
{
  Q_OBJECT

public:
  Layers(ImageModel* imageModel, QWidget* parent = nullptr);

private:
  // non-owning
  ImageModel* imageModel;

  // memory managed by Qt
  LayerList* layerList;
  QPushButton* addLayerButton;
  QPushButton* removeLayerButton;
};