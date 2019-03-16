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

  ImageModel* getImageModel() const { return imageModel.get(); }

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  static constexpr auto BACKGROUND_BLOCK_SIZE = 24;
  static constexpr auto INVERSE_BACKGROUND_BLOCK_SIZE = 1.0f / static_cast<float>(BACKGROUND_BLOCK_SIZE);
  static constexpr auto BACKGROUND_COLOR_BRIGHT = qRgb(100, 100, 100);
  static constexpr auto BACKGROUND_COLOR_DARK = qRgb(88, 88, 88);

  std::unique_ptr<ImageModel> imageModel;
  unsigned int scale;
  float inverseScale; // precalculated for performance
  bool drawGrid;

  void setScale(unsigned int scale);

  QPoint ScreenToImagePoint(const QPointF point) const;
};