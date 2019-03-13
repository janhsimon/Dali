#include "Image.hpp"

Image::Image(unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent)
{
  imageModel = std::make_unique<ImageModel>(width, height);
  
  setScale(4);
  drawGrid = false;

  connect(imageModel.get(), &ImageModel::paletteChanged, this, [&]() { repaint(); });
}

void Image::mousePressEvent(QMouseEvent *event)
{
  mouseMoveEvent(event);
}

void Image::mouseMoveEvent(QMouseEvent* event)
{
  if (event->buttons() & Qt::LeftButton)
  {
    const auto mousePosition = ScreenToImagePoint(event->localPos());

    if (mousePosition.x() < 0 || mousePosition.x() >= imageModel->getWidth() || mousePosition.y() < 0 || mousePosition.y() >= imageModel->getHeight())
    {
      return;
    }

    auto rectToRepaint = imageModel->drawOnSelectedLayer(mousePosition);
    repaint(QRect(rectToRepaint.x() * scale, rectToRepaint.y() * scale, rectToRepaint.width() * scale, rectToRepaint.height() * scale));
  }
}

void Image::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  // the rect uses on-screen pixel coordinates, so we need to convert it to image pixel coordinates
  // and since we could be seeing parts of image pixels, we need to include any border image pixels
  QRectF screenRect = event->rect();

  // divide the screen rect by scale to get image pixel coordinates
  screenRect.setX(screenRect.x() * inverseScale);
  screenRect.setY(screenRect.y() * inverseScale);
  screenRect.setWidth(screenRect.width() * inverseScale);
  screenRect.setHeight(screenRect.height() * inverseScale);

  // align the rect to include potential border image pixels
  const auto sourceRect = screenRect.toAlignedRect();
  const auto targetRect = QRect(sourceRect.x() * scale, sourceRect.y() * scale, sourceRect.width() * scale, sourceRect.height() * scale);

  // draw the background
  {
    const auto top = static_cast<int>(targetRect.top() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto left = static_cast<int>(targetRect.left() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto bottom = static_cast<int>(targetRect.bottom() * INVERSE_BACKGROUND_BLOCK_SIZE);
    const auto right = static_cast<int>(targetRect.right() * INVERSE_BACKGROUND_BLOCK_SIZE);

    for (auto y = top; y <= bottom; ++y)
    {
      for (auto x = left; x <= right; ++x)
      {
        const auto color = (x % 2 != y % 2) ? QColor(100, 100, 100) : QColor(88, 88, 88);
        painter.fillRect(QRect(x * BACKGROUND_BLOCK_SIZE, y * BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE), color);
      }
    }
  }

  for (auto i = 0u; i < imageModel->getLayerCount(); ++i)
  {
    painter.drawImage(targetRect, *imageModel->getLayerImage(i), sourceRect, Qt::ImageConversionFlag::NoFormatConversion);
  }
  
  if (drawGrid && scale >= 4)
  {
    painter.setPen(QPen(Qt::lightGray, 0));

    // draw vertical grid lines
    for (auto x = sourceRect.left(); x <= sourceRect.right(); ++x)
    {
      const auto lineX = x * scale;
      painter.drawLine(lineX, targetRect.top(), lineX, targetRect.bottom());
    }

    // draw horizontal grid lines
    for (auto y = sourceRect.top(); y <= sourceRect.bottom(); ++y)
    {
      const auto lineY = y * scale;
      painter.drawLine(targetRect.left(), lineY, targetRect.right(), lineY);
    }
  }
}

void Image::setScale(unsigned int scale)
{
  this->scale = scale;
  inverseScale = 1.0f / static_cast<float>(scale);
  setFixedSize(imageModel->getWidth() * scale, imageModel->getHeight() * scale);
}

QPoint Image::ScreenToImagePoint(const QPointF point) const
{
  return QPoint(point.x() * inverseScale, point.y() * inverseScale);
}