#pragma once

#include "MainArea.hpp"

class PreviewWindow : public QWidget
{
  Q_OBJECT

public:
  PreviewWindow(const MainArea* mainArea, QWidget* parent = nullptr);

private:
  static constexpr auto BACKGROUND_BLOCK_SIZE = 4;
  static constexpr auto INVERSE_BACKGROUND_BLOCK_SIZE = 1.0f / static_cast<float>(BACKGROUND_BLOCK_SIZE);
  static constexpr auto BACKGROUND_COLOR_BRIGHT = qRgb(100, 100, 100);
  static constexpr auto BACKGROUND_COLOR_DARK = qRgb(88, 88, 88);

  const MainArea* mainArea;

  void paintEvent(QPaintEvent* event);
};
