#pragma once

#include "ImageArea.hpp"

class Palette : public QWidget
{
  Q_OBJECT

public:
  Palette(const ImageArea* imageArea, QWidget* parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  constexpr static auto SWATCH_SIZE = 32u;
  constexpr static auto SWATCHES_PER_ROW = 4u;

  const ImageArea* imageArea;
};