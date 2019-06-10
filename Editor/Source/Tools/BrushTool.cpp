#include "BrushTool.hpp"

BrushTool::BrushTool(ImageModel* imageModel, BrushModel* brushModel) :
  imageModel(imageModel),
  brushModel(brushModel)
{
}

QRect BrushTool::mouseMove(const QPoint& mousePosition, bool isLeftMouseButtonDown)
{
  if (isLeftMouseButtonDown)
  {
    drawBrush(mousePosition);
  }
  
  return QRect(mousePosition.x(), mousePosition.y(), brushModel->getWidth(), brushModel->getHeight());
}

QRect BrushTool::mousePress(const QPoint& mousePosition, bool isLeftMouseButtonDown)
{
  return mouseMove(mousePosition, isLeftMouseButtonDown);
}

void BrushTool::drawBrush(const QPoint& mousePosition)
{
  for (auto brushY = 0; brushY < brushModel->getHeight(); ++brushY)
  {
    for (auto brushX = 0; brushX < brushModel->getWidth(); ++brushX)
    {
      if (!brushModel->getBrushAt(brushX, brushY))
      {
        continue;
      }

      const auto x = mousePosition.x() + brushX;
      const auto y = mousePosition.y() + brushY;

      if (x >= 0 && x < imageModel->getWidth() && y >= 0 && y < imageModel->getHeight())
      {
        imageModel->setPixel(imageModel->getSelectedLayerIndex(), x, y, imageModel->getSelectedPaletteColorIndex());
      }
    }
  }

  // emit the imageChanged signal of the image model now that modifications are processed
  const auto imageRect = QRect(mousePosition.x(), mousePosition.y(), brushModel->getWidth(), brushModel->getHeight());
  emit imageModel->imageChanged(imageRect);
}