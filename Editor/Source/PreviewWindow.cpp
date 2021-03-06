#include "PreviewWindow.hpp"

PreviewWindow::PreviewWindow(const TabArea* tabArea, QWidget* parent) :
  QWidget(parent),
  tabArea(tabArea)
{
  setWindowTitle("Preview");
  setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

  
  if (const auto currentImageModel = tabArea->getCurrentImageModel(); currentImageModel)
  {
    setFixedSize(currentImageModel->getWidth(), currentImageModel->getHeight());
  }
  else
  {
    setFixedSize(320, 200);
  }

  connect(tabArea, &TabArea::currentChanged, this, [&]()
  {
    if (const auto currentImageModel = this->tabArea->getCurrentImageModel(); currentImageModel)
    {
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
  const auto currentImageModel = tabArea->getCurrentImageModel();

  if (!currentImageModel)
  {
    return;
  }

  QPainter painter(this);

  const auto rect = event->rect();

  // draw the background
  {
    const auto top = static_cast<int>(rect.top() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto left = static_cast<int>(rect.left() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto bottom = static_cast<int>(rect.bottom() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto right = static_cast<int>(rect.right() * INVERSE_BACKGROUND_BLOCK_SIZE);

    for (auto y = top; y <= bottom; ++y)
    {
      for (auto x = left; x <= right; ++x)
      {
        const auto color = (x % 2 != y % 2) ? BACKGROUND_COLOR_BRIGHT : BACKGROUND_COLOR_DARK;
        painter.fillRect(QRect(x * BACKGROUND_BLOCK_SIZE, y * BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE), color);
      }
    }
  }

  for (auto i = currentImageModel->getLayerCount(); i > 0u; --i)
  // reverse-iterate through layers to draw the bottom layer first
  {
    // avoid issues with unsigned integer overflow
    const auto layerIndex = i - 1u;

    if (currentImageModel->getLayerVisible(layerIndex))
    {
      painter.drawImage(rect, *currentImageModel->getLayerImage(layerIndex), rect, Qt::NoFormatConversion);
    }
  }
}