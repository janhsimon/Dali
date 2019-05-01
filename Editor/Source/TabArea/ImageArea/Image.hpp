#pragma once

#include "../../Models/ImageModel.hpp"

class Image : public QWidget
{
  Q_OBJECT

public:
  Image(const BrushModel* brushModel, unsigned int width, unsigned int height, QWidget* parent = nullptr);

  void zoomIn() { setScale(std::min(++scale, 128u)); }
  void zoomOut() { setScale(std::max(--scale, 1u)); }

  const bool getDrawGrid() const { return drawGrid; }
  void setDrawGrid(bool drawGrid) { this->drawGrid = drawGrid; repaint(); }

  ImageModel* getImageModel() const { return imageModel.get(); }

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  static constexpr auto BACKGROUND_BLOCK_SIZE = 24;
  static constexpr auto INVERSE_BACKGROUND_BLOCK_SIZE = 1.0f / static_cast<float>(BACKGROUND_BLOCK_SIZE);
  static constexpr auto BACKGROUND_COLOR_BRIGHT = qRgb(100, 100, 100);
  static constexpr auto BACKGROUND_COLOR_DARK = qRgb(88, 88, 88);

  const BrushModel* brushModel;
  std::unique_ptr<ImageModel> imageModel;
  unsigned int scale;
  float inverseScale; // precalculated for performance
  bool drawGrid;
  QPoint mousePosition; // in image space
  bool isLeftMouseButtonDown;
  QRect rectToOverwrite; // in screen space

  void update();

  void setScale(unsigned int scale);

  QPoint screenToImagePoint(const QPointF point) const;
  bool doesImageContainPoint(const QPoint point) const;
};