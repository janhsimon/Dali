#include "ImageModel.hpp"

ImageModel::ImageModel(unsigned int width, unsigned int height) :
  width(width),
  height(height)
{
  paletteColors.reserve(1 + 16);
  paletteColors.push_back(qRgba(0, 0, 0, 0));
  for (auto i = 0u; i < 16u; ++i)
  {
    paletteColors.push_back(qRgba(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255));
  }

  selectedPaletteColorIndex = 0u;
  
  addLayer();
}

QRgb ImageModel::getPaletteColorAtIndex(unsigned int index) const
{
  // take into account that we have an internal first palette color
  return paletteColors[index + 1];
}

void ImageModel::setPaletteColorAtIndex(const unsigned int index, const QRgb color)
{
  // take into account that we have an internal first palette color
  paletteColors[index + 1] = color;

  for (auto& layer : layers)
  {
    layer->setColorTable(paletteColors);
  }

  emit paletteChanged();
}

unsigned int ImageModel::getPaletteColorCount() const
{
  // take into account that we have an internal first palette color
  return static_cast<unsigned int>(paletteColors.size()) - 1u;
}

void ImageModel::setSelectedPaletteColorIndex(const unsigned int selectedPaletteColorIndex)
{
  this->selectedPaletteColorIndex = selectedPaletteColorIndex;
  emit selectedPaletteColorIndexChanged();
}

void ImageModel::addLayer()
{
  layers.push_back(std::make_unique<QImage>(width, height, QImage::Format::Format_Indexed8));
  layers.back()->setColorTable(paletteColors);

  // set all indices to the internal first palette color (fully transparent)
  memset(layers.back()->bits(), 0, layers.back()->sizeInBytes());

  setSelectedLayerIndex(static_cast<unsigned int>(layers.size()) - 1u);

  // do not emit the layersChanged signal as adding a transparent layer can not change the image
}

void ImageModel::removeSelectedLayer()
{
  layers.erase(layers.begin() + selectedLayerIndex);

  // emit the layersChanged signal as removing a layer is likely to cause a change in the image
  emit layersChanged();
}

QRect ImageModel::drawOnSelectedLayer(const QPoint point)
{
  // TODO: this is simulating a brush tool, move this code there later

  constexpr unsigned char brush[] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };
  auto brushStartX = -1, brushStartY = -1;
  auto brushEndX = 1, brushEndY = 1;
  const auto brushSizeX = (brushEndX - brushStartX) + 1;
  const auto brushSizeY = (brushEndY - brushStartY) + 1;

  if (point.x() + brushStartX < 0)
  {
    brushStartX = 0;
  }

  if (point.x() + brushEndX >= width)
  {
    brushEndX = 0;
  }

  if (point.y() + brushStartY < 0)
  {
    brushStartY = 0;
  }

  if (point.y() + brushEndY >= height)
  {
    brushEndY = 0;
  }

  for (auto brushY = brushStartY; brushY <= brushEndY; ++brushY)
  {
    for (auto brushX = brushStartX; brushX <= brushEndX; ++brushX)
    {
      if (brush[(brushY + 1) * brushSizeX + brushX + 1] == 1)
      {
        const auto i = point.x() + brushX;
        const auto j = point.y() + brushY;

        // take into account that we have an internal first palette color
        layers[selectedLayerIndex]->scanLine(j)[i] = getSelectedPaletteColorIndex() + 1;
      }
    }
  }

  emit imageChanged();

  return QRect(point.x() + brushStartX, point.y() + brushStartY, brushSizeX, brushSizeY);
}