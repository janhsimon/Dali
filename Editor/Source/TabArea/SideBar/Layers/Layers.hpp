#pragma once

#include "LayerList.hpp"

class Layers : public QWidget
{
  Q_OBJECT

public:
  Layers(ImageModel* imageModel, QWidget* parent = nullptr);

private:
  ImageModel* imageModel;
  std::unique_ptr<LayerList> layerList;
  QPushButton* addLayerButton;
  QPushButton* removeLayerButton;
};