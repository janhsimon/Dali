#include "Image.hpp"

Image::Image(const BrushModel* brushModel, unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent),
  brushModel(brushModel),
  drawGrid(false),
  mousePosition(-1, -1),
  isLeftMouseButtonDown(false),
  rectToOverwrite(0, 0, 0, 0)
{
  imageModel = std::make_unique<ImageModel>(brushModel, width, height);

  setScale(4);

  // receive mouse move events even when no mouse buttons are pressed
  setMouseTracking(true);
  
  setCursor(Qt::CrossCursor);

  connect(imageModel.get(), &ImageModel::paletteChanged, this, [&]() { repaint(); });
  connect(imageModel.get(), &ImageModel::layersChanged, this, [&]() { repaint(); });

  // it is possible to connect to the image changed signal of the image model
  // here to redraw but calling repaint directly gives better performance
}

void Image::mousePressEvent(QMouseEvent *event)
{
  mouseMoveEvent(event);
}

void Image::mouseMoveEvent(QMouseEvent* event)
{
  // retrieve the mouse position in image space
  mousePosition = screenToImagePoint(event->localPos());
  isLeftMouseButtonDown = event->buttons() & Qt::LeftButton;
  update();
}

void Image::leaveEvent(QEvent* event)
{
  mousePosition.setX(-1);
  mousePosition.setY(-1);
  update();
}

void Image::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  QRectF screenRect = event->rect();

  // divide the screen rect by scale to get image pixel coordinates
  screenRect.setX(screenRect.x() * inverseScale);
  screenRect.setY(screenRect.y() * inverseScale);
  screenRect.setWidth(screenRect.width() * inverseScale);
  screenRect.setHeight(screenRect.height() * inverseScale);

  // align the rect to include potential border image pixels
  // that may have been partially covered by the screen rect
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
      const auto target = QRect(screenMousePosition.x(), screenMousePosition.y(), brushModel->getWidth() * scale, brushModel->getHeight() * scale);
      const auto source = QRect(0, 0, brushModel->getWidth(), brushModel->getHeight());
      painter.drawImage(target, *brushModel->getBrushImage(), source, Qt::ImageConversionFlag::NoFormatConversion);
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

void Image::update()
{
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

  if (isLeftMouseButtonDown)
  {
    imageModel->drawOnSelectedLayer(mousePosition);
  }

  const auto screenRect = QRect(mousePosition.x() * scale, mousePosition.y() * scale, brushModel->getWidth() * scale, brushModel->getHeight() * scale);
  repaint(screenRect);

  rectToOverwrite = screenRect;
}

void Image::setScale(unsigned int scale)
{
  this->scale = scale;
  inverseScale = 1.0f / static_cast<float>(scale);
  setFixedSize(imageModel->getWidth() * scale, imageModel->getHeight() * scale);
}

QPoint Image::screenToImagePoint(const QPointF point) const
{
  return QPoint(point.x() * inverseScale, point.y() * inverseScale);
}

bool Image::doesImageContainPoint(const QPoint point) const
{
  return mousePosition.x() >= 0 && mousePosition.x() < imageModel->getWidth() && mousePosition.y() >= 0 && mousePosition.y() < imageModel->getHeight();
}