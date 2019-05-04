#pragma once

#include "../Models/BrushModel.hpp"
#include "../TabArea/TabArea.hpp"

class Brush : public QWidget
{
  Q_OBJECT

public:
  Brush(const TabArea* tabArea, QWidget* parent = nullptr);

  BrushModel* getBrushModel() const { return brushModel.get(); }

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  static constexpr auto BACKGROUND_BLOCK_SIZE = 4;
  static constexpr auto INVERSE_BACKGROUND_BLOCK_SIZE = 1.0f / static_cast<float>(BACKGROUND_BLOCK_SIZE);
  static constexpr auto BACKGROUND_COLOR_BRIGHT = qRgb(100, 100, 100);
  static constexpr auto BACKGROUND_COLOR_DARK = qRgb(88, 88, 88);

  const TabArea* tabArea;
  std::unique_ptr<BrushModel> brushModel;
  float inverseScaleX, inverseScaleY; // precalculated for performance

  void update(const QMouseEvent* event);
};