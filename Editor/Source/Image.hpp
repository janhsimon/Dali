#pragma once

#include "ImageModel.hpp"

class Image : public QWidget
{
  Q_OBJECT

public:
  Image(unsigned int width, unsigned int height, QWidget* parent = nullptr);

  void zoomIn() { setScale(std::min(++scale, 128u)); }
  void zoomOut() { setScale(std::max(--scale, 1u)); }

  const bool getDrawGrid() const { return drawGrid; }
  void setDrawGrid(bool drawGrid) { this->drawGrid = drawGrid; repaint(); }

  const PaletteModel* getPaletteModel() const { return paletteModel.get(); }
  const ImageModel* getImageModel() const { return imageModel.get(); }

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  std::unique_ptr<PaletteModel> paletteModel;
  std::unique_ptr<ImageModel> imageModel;
  unsigned int scale;
  float inverseScale; // precalculated for performance
  bool drawGrid;

  void setScale(unsigned int scale);
  bool convertScreenToImage(const QPointF point, int& x, int& y) const;
};