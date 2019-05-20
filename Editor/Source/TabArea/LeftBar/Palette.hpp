#pragma once

#include "../../Models/ImageModel.hpp"

class Palette : public QWidget
{
  Q_OBJECT

public:
  Palette(ImageModel* imageModel, QWidget* parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  constexpr static auto SWATCH_SIZE = 32u;
  constexpr static auto SWATCHES_PER_ROW = 4u;

  // non-owning
  ImageModel* imageModel;
};