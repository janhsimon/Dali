#pragma once

#include "../../Models/ImageModel.hpp"

class Layers : public QWidget
{
  Q_OBJECT

public:
  Layers(ImageModel* imageModel, QWidget* parent = nullptr);

private:
  std::unique_ptr<QListWidget> layerList;
  QPushButton* addLayerButton;
  QPushButton* removeLayerButton;

  ImageModel* imageModel;
};