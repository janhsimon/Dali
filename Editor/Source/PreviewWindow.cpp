#include "PreviewWindow.hpp"

PreviewWindow::PreviewWindow(const TabArea* tabArea, QWidget* parent) :
  tabArea(tabArea),
  QWidget(parent)
{
  setWindowTitle("Preview");
  setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

  const auto currentImage = tabArea->getCurrentImage();
  if (currentImage)
  {
    const auto currentImageModel = currentImage->getImageModel();
    setFixedSize(currentImageModel->getWidth(), currentImageModel->getHeight());
  }
  else
  {
    setFixedSize(320, 200);
  }

  connect(tabArea, &TabArea::currentChanged, this, [&]()
  {
    const auto currentImage = this->tabArea->getCurrentImage();

    if (currentImage)
    {
      const auto currentImageModel = currentImage->getImageModel();
      setFixedSize(currentImageModel->getWidth(), currentImageModel->getHeight());

      connect(currentImageModel, &ImageModel::paletteChanged, this, [&]() { repaint(); });
      connect(currentImageModel, &ImageModel::layersChanged, this, [&]() { repaint(); });
      connect(currentImageModel, &ImageModel::imageChanged, this, [&](const QRect& imageRect) { repaint(imageRect); });
    }

    repaint();
  });
}

void PreviewWindow::paintEvent(QPaintEvent* event)
{
  const auto currentImage = tabArea->getCurrentImage();

  if (!currentImage)
  {
    return;
  }

  QPainter painter(this);

  const auto imageRect = event->rect();

  // draw the background
  {
    const auto top = static_cast<int>(imageRect.top() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto left = static_cast<int>(imageRect.left() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto bottom = static_cast<int>(imageRect.bottom() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto right = static_cast<int>(imageRect.right() * INVERSE_BACKGROUND_BLOCK_SIZE);

    for (auto y = top; y <= bottom; ++y)
    {
      for (auto x = left; x <= right; ++x)
      {
        const auto color = (x % 2 != y % 2) ? BACKGROUND_COLOR_BRIGHT : BACKGROUND_COLOR_DARK;
        painter.fillRect(QRect(x * BACKGROUND_BLOCK_SIZE, y * BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE), color);
      }
    }
  }

  const auto currentImageModel = currentImage->getImageModel();
  for (auto i = currentImageModel->getLayerCount(); i > 0u; --i)
  // reverse-iterate through layers to draw the bottom layer first
  {
    painter.drawImage(imageRect, *currentImageModel->getLayerImage(i - 1u), imageRect, Qt::ImageConversionFlag::NoFormatConversion);
  }
}