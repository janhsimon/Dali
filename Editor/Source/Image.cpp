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

    auto rectToRepaint = imageModel->setPixels(mousePosition);
    repaint(QRect(rectToRepaint.x() * scale, rectToRepaint.y() * scale, rectToRepaint.width() * scale, rectToRepaint.height() * scale));
  }
}

void Image::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  // the rect uses on-screen pixel coordinates, so we need to convert it to image pixel coordinates
  // and since we could be seeing parts of image pixels, we need to include any border image pixels
  const auto screenRect = event->rect();

  // divide the screen rect by scale to get image pixel coordinates
  auto tempRect = QRectF(screenRect);
  tempRect.setX(tempRect.x() * inverseScale);
  tempRect.setY(tempRect.y() * inverseScale);
  tempRect.setWidth(tempRect.width() * inverseScale);
  tempRect.setHeight(tempRect.height() * inverseScale);

  // align the rect to include potential border image pixels
  const auto sourceRect = tempRect.toAlignedRect();
  const auto targetRect = QRect(sourceRect.x() * scale, sourceRect.y() * scale, sourceRect.width() * scale, sourceRect.height() * scale);
  painter.drawImage(targetRect, *imageModel->getImage(), sourceRect, Qt::ImageConversionFlag::NoFormatConversion);
  
  if (drawGrid && scale >= 4)
  {
    painter.setPen(QPen(Qt::darkGray, 0));

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