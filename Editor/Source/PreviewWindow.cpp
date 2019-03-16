#include "PreviewWindow.hpp"

PreviewWindow::PreviewWindow(const MainArea* mainArea, QWidget* parent) :
  mainArea(mainArea),
  QWidget(parent)
{
  setWindowTitle("Preview");
  setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

  const auto currentImage = mainArea->getCurrentImage();
  if (currentImage)
  {
    const auto currentImageModel = currentImage->getImageModel();
    setFixedSize(currentImageModel->getWidth(), currentImageModel->getHeight());
  }
  else
  {
    setFixedSize(320, 200);
  }

  connect(mainArea, &MainArea::currentChanged, this, [&]()
  {
    const auto currentImage = this->mainArea->getCurrentImage();

    if (currentImage)
    {
      const auto currentImageModel = currentImage->getImageModel();
      setFixedSize(currentImageModel->getWidth(), currentImageModel->getHeight());

      connect(currentImageModel, &ImageModel::paletteChanged, this, [&]() { repaint(); });
      connect(currentImageModel, &ImageModel::layersChanged, this, [&]() { repaint(); });
      connect(currentImageModel, &ImageModel::imageChanged, this, [&]() { repaint(); });
    }

    repaint();
  });
}

void PreviewWindow::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  // draw the background
  {
    const auto top = static_cast<int>(event->rect().top() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto left = static_cast<int>(event->rect().left() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto bottom = static_cast<int>(event->rect().bottom() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto right = static_cast<int>(event->rect().right() * INVERSE_BACKGROUND_BLOCK_SIZE);

    for (auto y = top; y <= bottom; ++y)
    {
      for (auto x = left; x <= right; ++x)
      {
        const auto color = (x % 2 != y % 2) ? BACKGROUND_COLOR_BRIGHT : BACKGROUND_COLOR_DARK;
        painter.fillRect(QRect(x * BACKGROUND_BLOCK_SIZE, y * BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE), color);
      }
    }
  }

  const auto currentImage = mainArea->getCurrentImage();

  if (!currentImage)
  {
    return;
  }

  const auto currentImageModel = currentImage->getImageModel();

  for (auto i = static_cast<int>(currentImageModel->getLayerCount()) - 1; i >= 0; --i)
  // reverse-iterate through layers to draw the bottom layer first
  {
    painter.drawImage(event->rect(), *currentImageModel->getLayerImage(static_cast<unsigned int>(i)), event->rect(), Qt::ImageConversionFlag::NoFormatConversion);
  }
}