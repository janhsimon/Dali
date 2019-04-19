#include "Image.hpp"

Image::Image(unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent),
  drawGrid(false),
  mousePosition(-1, -1),
  rectToOverwrite(0, 0, 0, 0)
{
  imageModel = std::make_unique<ImageModel>(width, height);

  setScale(4);

  // receive mouse move events even when no mouse buttons are pressed
  setMouseTracking(true);

  connect(imageModel.get(), &ImageModel::paletteChanged, this, [&]() { repaint(); });
  connect(imageModel.get(), &ImageModel::layersChanged, this, [&]() { repaint(); });

  // we could connect to the image model's image changed signal here to
  // redraw but instead we call repaint directly for optimal performance
}

void Image::mousePressEvent(QMouseEvent *event)
{
  mouseMoveEvent(event);
}

void Image::mouseMoveEvent(QMouseEvent* event)
{
  // retrieve the mouse position in image space
  mousePosition = ScreenToImagePoint(event->localPos());

  if (!rectToOverwrite.isNull())
  {
    repaint(rectToOverwrite);
  }

  if (!doesImageContainPoint(mousePosition))
  {
    rectToOverwrite.setWidth(0);
    rectToOverwrite.setHeight(0);
    return;
  }

  if (event->buttons() & Qt::LeftButton)
  {
    imageModel->drawOnSelectedLayer(mousePosition);
  }

  // TODO: get hardcoded brush sizes from image model instead, later use a brush class
  const auto screenRect = QRect((mousePosition.x() - 1) * scale, (mousePosition.y() - 1) * scale, 3 * scale, 3 * scale);
  repaint(screenRect);
  
  rectToOverwrite = screenRect;
}

void Image::leaveEvent(QEvent* event)
{
  auto mouseEvent = QMouseEvent(QEvent::MouseMove, QPointF(-1.0f, -1.0f), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
  mouseMoveEvent(&mouseEvent);
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
        const auto color = (x % 2 != y % 2) ? BACKGROUND_COLOR_BRIGHT : BACKGROUND_COLOR_DARK;
        painter.fillRect(QRect(x * BACKGROUND_BLOCK_SIZE, y * BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE, BACKGROUND_BLOCK_SIZE), color);
      }
    }
  }

  // draw the image layers
  {
    for (auto i = imageModel->getLayerCount(); i > 0u; --i)
    // reverse-iterate through layers to draw the bottom layer first
    {
      // avoid issues with unsigned integer overflow
      const auto layerIndex = i - 1u;
      painter.drawImage(targetRect, *imageModel->getLayerImage(layerIndex), sourceRect, Qt::ImageConversionFlag::NoFormatConversion);
    }
  }

  // draw the foreground
  {
    const auto screenMousePosition = QPoint(mousePosition.x() * scale, mousePosition.y() * scale);
    if (targetRect.contains(screenMousePosition))
    {
      painter.fillRect(QRect(screenMousePosition.x(), screenMousePosition.y(), scale, scale), imageModel->getPaletteColorAtIndex(imageModel->getSelectedPaletteColorIndex()));
    }
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

bool Image::doesImageContainPoint(const QPoint point) const
{
  return mousePosition.x() >= 0 && mousePosition.x() < imageModel->getWidth() && mousePosition.y() >= 0 && mousePosition.y() < imageModel->getHeight();
}