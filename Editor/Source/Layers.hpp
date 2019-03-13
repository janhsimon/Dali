#pragma once

#include "ImageModel.hpp"

class Layers : public QWidget
{
public:
  Layers(ImageModel* imageModel, QWidget* parent = nullptr);

private:
  std::unique_ptr<QListWidget> layerList;
  QPushButton* addLayerButton;
  QPushButton* removeLayerButton;

  ImageModel* imageModel;
};