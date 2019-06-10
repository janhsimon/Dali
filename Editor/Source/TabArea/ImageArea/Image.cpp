#include "Image.hpp"

Image::Image(ImageModel* imageModel, const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent) :
  QWidget(parent),
  imageModel(imageModel),
  toolModel(toolModel),
  drawGrid(false),
  mousePosition(-1, -1),
  isLeftMouseButtonDown(false)
{
  brushTool = std::make_unique<BrushTool>(imageModel, toolModel->getBrushModel());

  setScale(4);

  // receive mouse move events even when no mouse buttons are pressed
  setMouseTracking(true);
  
  setCursor(Qt::CrossCursor);

  connect(imageModel, &ImageModel::paletteChanged, this, [&]() { repaint(); });
  connect(imageModel, &ImageModel::layersChanged, this, [&]() { repaint(); });

  // it is possible to connect to the image changed signal of the image model
  // here to redraw but calling repaint directly gives better performance
}

void Image::mousePressEvent(QMouseEvent *event)
{
  // retrieve the mouse position in image space
  mousePosition = screenToImagePoint(event->localPos());
  isLeftMouseButtonDown = event->buttons() & Qt::LeftButton;
  
  if (!imageModel->getLayerVisible(imageModel->getSelectedLayerIndex()))
  // do not allow tools when the selected layer is invisible
  {
    return;
  }

  if (toolModel->getSelectedTool() == Tool::BRUSH)
  {
    if (!updateDirtyRect())
    {
      return;
    }

    const auto imageRect = brushTool->mousePress(mousePosition, isLeftMouseButtonDown);
    const auto screenRect = QRect(imageRect.x() * scale, imageRect.y() * scale, imageRect.width() * scale, imageRect.height() * scale);
    repaint(screenRect);

    imageModel->setDirtyRect(screenRect);
  }
  else if (toolModel->getSelectedTool() == Tool::LINE)
  {
    // TODO
  }
}

void Image::mouseMoveEvent(QMouseEvent* event)
{
  // retrieve the mouse position in image space
  mousePosition = screenToImagePoint(event->localPos());
  isLeftMouseButtonDown = event->buttons() & Qt::LeftButton;
  
  if (!imageModel->getLayerVisible(imageModel->getSelectedLayerIndex()))
  // do not allow tools when the selected layer is invisible
  {
    return;
  }

  if (toolModel->getSelectedTool() == Tool::BRUSH)
  {
    if (!updateDirtyRect())
    {
      return;
    }

    const auto imageRect = brushTool->mouseMove(mousePosition, isLeftMouseButtonDown);
    const auto screenRect = QRect(imageRect.x() * scale, imageRect.y() * scale, imageRect.width() * scale, imageRect.height() * scale);
    repaint(screenRect);

    imageModel->setDirtyRect(screenRect);
  }
  else if (toolModel->getSelectedTool() == Tool::LINE)
  {
    // TODO
  }
}

void Image::leaveEvent(QEvent* event)
{
  mousePosition.setX(-1);
  mousePosition.setY(-1);
  updateDirtyRect();
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

      if (imageModel->getLayerVisible(layerIndex))
      {
        painter.drawImage(targetRect, *imageModel->getLayerImage(layerIndex), sourceRect, Qt::ImageConversionFlag::NoFormatConversion);
      }
    }
  }

  // draw the foreground
  {
    const auto screenMousePosition = QPoint(mousePosition.x() * scale, mousePosition.y() * scale);
    if (targetRect.contains(screenMousePosition))
    {
      const auto brushModel = toolModel->getBrushModel();
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

bool Image::updateDirtyRect()
{
  const auto dirtyRect = imageModel->getDirtyRect();
  if (!dirtyRect.isNull())
  {
    repaint(dirtyRect);
  }

  if (!doesImageContainPoint(mousePosition))
  {
    imageModel->setDirtyRect(QRect());
    return false;
  }

  return true;
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