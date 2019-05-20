#include "Palette.hpp"

Palette::Palette(ImageModel* imageModel, QWidget* parent) :
  QWidget(parent),
  imageModel(imageModel)
{
  const auto numRows = imageModel->getPaletteColorCount() / SWATCHES_PER_ROW + 1;
  setFixedSize(SWATCHES_PER_ROW * SWATCH_SIZE + (SWATCHES_PER_ROW - 1) * 2 + 2, numRows * SWATCH_SIZE + (numRows - 1) * 2 + 2);

  connect(imageModel, &ImageModel::paletteChanged, this, [&]() { repaint(); });
  connect(imageModel, &ImageModel::selectedPaletteColorIndexChanged, this, [&]() { repaint(); });
}

void Palette::mousePressEvent(QMouseEvent* event)
{
  const auto leftMouseButtonDown = event->buttons() & Qt::LeftButton;
  const auto rightMouseButtonDown = event->buttons() & Qt::RightButton;

  if (leftMouseButtonDown && !rightMouseButtonDown)
  {
    const auto i = event->x() / (SWATCH_SIZE + 2);
    const auto j = event->y() / (SWATCH_SIZE + 2);

    imageModel->setSelectedPaletteColorIndex(j * SWATCHES_PER_ROW + i);
  }
  else if (rightMouseButtonDown && !leftMouseButtonDown)
  {
    const auto i = event->x() / (SWATCH_SIZE + 2);
    const auto j = event->y() / (SWATCH_SIZE + 2);

    imageModel->setPaletteColorAtIndex(j * SWATCHES_PER_ROW + i, qRgb(std::rand() % 255, std::rand() % 255, std::rand() % 255));
  }
}

void Palette::paintEvent(QPaintEvent* event)
{
  QPainter painter(this);

  for (auto i = 0u; i < imageModel->getPaletteColorCount(); ++i)
  {
    const auto x = i % SWATCHES_PER_ROW;
    const auto y = i / SWATCHES_PER_ROW;

    painter.fillRect(1 + x * SWATCH_SIZE + x * 2, 1 + y * SWATCH_SIZE + y * 2, SWATCH_SIZE, SWATCH_SIZE, imageModel->getPaletteColorAtIndex(i));

    if (i == imageModel->getSelectedPaletteColorIndex())
    {
      painter.setPen(Qt::black);
      painter.drawRect(x * SWATCH_SIZE + x * 2, y * SWATCH_SIZE + y * 2, SWATCH_SIZE + 1, SWATCH_SIZE + 1);

      painter.setPen(Qt::white);
      painter.drawRect(1 + x * SWATCH_SIZE + x * 2, 1 + y * SWATCH_SIZE + y * 2, SWATCH_SIZE - 1, SWATCH_SIZE - 1);
    }
  }
}