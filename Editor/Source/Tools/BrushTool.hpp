#pragma once

#include "../Models/ImageModel.hpp"

class BrushTool : public QObject
{
  Q_OBJECT

public:
  BrushTool(ImageModel* imageModel, BrushModel* brushModel);

  // return the affected rect in image space
  QRect mouseMove(const QPoint& mousePosition, bool isLeftMouseButtonDown);
  QRect mousePress(const QPoint& mousePosition, bool isLeftMouseButtonDown);

private:
  // non-owning
  ImageModel* imageModel;
  BrushModel* brushModel;

  void drawBrush(const QPoint& mousePosition);
};