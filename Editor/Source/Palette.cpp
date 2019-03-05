#include "Palette.hpp"

Palette::Palette(const ImageArea* imageArea_, QWidget* parent) :
  imageArea(imageArea_),
  QWidget(parent)
{
  const auto currentImage = imageArea->getCurrentImage();

  if (currentImage)
  {
    const auto numRows = currentImage->getImageModel()->getPaletteColorCount() / SWATCHES_PER_ROW + 1;
    setFixedSize(SWATCHES_PER_ROW * SWATCH_SIZE + (SWATCHES_PER_ROW - 1) * 2 + 2, numRows * SWATCH_SIZE + (numRows - 1) * 2 + 2);
    connect(currentImage->getImageModel(), &ImageModel::paletteChanged, this, [&](int index) { repaint(); });
  }
  
  connect(imageArea, &QTabWidget::currentChanged, this, [&](int index)
  {
    const auto currentImage = imageArea->getCurrentImage();

    if (currentImage)
    {
      const auto numRows = currentImage->getImageModel()->getPaletteColorCount() / SWATCHES_PER_ROW + 1;
      setFixedSize(SWATCHES_PER_ROW * SWATCH_SIZE + (SWATCHES_PER_ROW - 1) * 2 + 2, numRows * SWATCH_SIZE + (numRows - 1) * 2 + 2);
      connect(currentImage->getImageModel(), &ImageModel::paletteChanged, this, [&](int index) { repaint(); });
    }

    repaint();
  });
}

void Palette::mousePressEvent(QMouseEvent* event)
{
  if (event->buttons() & Qt::LeftButton)
  {
    const auto currentImage = imageArea->getCurrentImage();

    if (!currentImage)
    {
      return;
    }

    const auto i = event->x() / (SWATCH_SIZE + 2);
    const auto j = event->y() / (SWATCH_SIZE + 2);

    auto imageModel = currentImage->getImageModel();
    imageModel->setPaletteColorAtIndex(j * SWATCHES_PER_ROW + i, qRgb(std::rand() % 255, std::rand() % 255, std::rand() % 255));
  }
}

void Palette::paintEvent(QPaintEvent* event)
{
  const auto currentImage = imageArea->getCurrentImage();

  if (!currentImage)
  {
    return;
  }

  const auto imageModel = currentImage->getImageModel();

  QPainter painter(this);

  for (auto i = 0u; i < imageModel->getPaletteColorCount(); ++i)
  {
    const auto x = i % SWATCHES_PER_ROW;
    const auto y = i / SWATCHES_PER_ROW;

    painter.fillRect(1 + x * SWATCH_SIZE + x * 2, 1 + y * SWATCH_SIZE + y * 2, SWATCH_SIZE, SWATCH_SIZE, imageModel->getPaletteColorAtIndex(i));
  }
}