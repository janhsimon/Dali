#include "Brush.hpp"

Brush::Brush(QWidget* parent) :
  QWidget(parent)
{
  setFixedSize(96, 96);

  brushModel = std::make_unique<BrushModel>();

  inverseScaleX = static_cast<float>(width()) / static_cast<float>(brushModel->getWidth());
  inverseScaleY = static_cast<float>(height()) / static_cast<float>(brushModel->getHeight());

  connect(brushModel.get(), &BrushModel::colorChanged, this, [&]() { repaint(); });
}

void Brush::mousePressEvent(QMouseEvent *event)
{
  update(event);
}

void Brush::mouseMoveEvent(QMouseEvent* event)
{
  update(event);
}

void Brush::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  QRectF screenRect = event->rect();

  // divide the screen rect by scale to get image pixel coordinates
  screenRect.setX(screenRect.x() / inverseScaleX);
  screenRect.setY(screenRect.y() / inverseScaleY);
  screenRect.setWidth(screenRect.width() / inverseScaleX);
  screenRect.setHeight(screenRect.height() / inverseScaleY);

  // align the rect to include potential border image pixels
  // that may have been partially covered by the screen rect
  const auto sourceRect = screenRect.toAlignedRect();
  const auto targetRect = QRectF(sourceRect.x() * inverseScaleX, sourceRect.y() * inverseScaleY, sourceRect.width() * inverseScaleX, sourceRect.height() * inverseScaleY).toAlignedRect();

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

  painter.drawImage(targetRect, *brushModel->getBrushImage(), sourceRect, Qt::NoFormatConversion);

  painter.setPen(QPen(Qt::lightGray, 0));

  // draw vertical grid lines
  for (auto x = sourceRect.left(); x <= sourceRect.right(); ++x)
  {
    const auto lineX = x * inverseScaleX;
    painter.drawLine(lineX, targetRect.top(), lineX, targetRect.bottom());
  }

  // draw horizontal grid lines
  for (auto y = sourceRect.top(); y <= sourceRect.bottom(); ++y)
  {
    const auto lineY = y * inverseScaleY;
    painter.drawLine(targetRect.left(), lineY, targetRect.right(), lineY);
  }
}

void Brush::update(const QMouseEvent* event)
{
  const auto left = static_cast<bool>(event->buttons() & Qt::LeftButton);
  const auto right = static_cast<bool>(event->buttons() & Qt::RightButton);

  if (left == right)
  {
    return;
  }

  const auto mousePosition = event->localPos();
  const auto i = static_cast<int>(mousePosition.x() / inverseScaleX);
  const auto j = static_cast<int>(mousePosition.y() / inverseScaleY);

  if (i >= 0 && i < brushModel->getWidth() && j >= 0 && j < brushModel->getHeight())
  {
    brushModel->setBrushAt(i, j, left);

    const auto screenRect = QRectF(i * inverseScaleX, j * inverseScaleY, inverseScaleX, inverseScaleY).toAlignedRect();
    repaint(screenRect);
  }
}