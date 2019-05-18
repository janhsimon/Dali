#pragma once

#include "../../../Models/ImageModel.hpp"

class LayerListItem : public QWidget
{
  Q_OBJECT

public:
  LayerListItem(const QString& layerName, ImageModel* imageModel, QListWidget* listWidget = nullptr);

private:
  ImageModel* imageModel;
  QListWidget* listWidget;
  QLineEdit *layerNameLineEdit;
};