#include "ImageModel.hpp"

#include <cassert>

ImageModel::ImageModel(const ToolModel* toolModel, unsigned int width, unsigned int height) :
  toolModel(toolModel),
  width(width),
  height(height)
{
  // allocate an internal first palette color for transparency
  paletteColors.reserve(1 + 16);
  paletteColors.push_back(qRgba(0, 0, 0, 0));
  for (auto i = 0u; i < 16u; ++i)
  {
    paletteColors.push_back(qRgba(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255));
  }

  selectedPaletteColorIndex = 0u;

  connect(this, &ImageModel::selectedPaletteColorIndexChanged, this, [&]() { this->toolModel->getBrushModel()->setColor(getSelectedPaletteColor()); });
  connect(this, &ImageModel::paletteChanged, this, [&]() { this->toolModel->getBrushModel()->setColor(getSelectedPaletteColor()); });

  toolModel->getBrushModel()->setColor(getSelectedPaletteColor());

  addLayer();
}

QRgb ImageModel::getPaletteColorAtIndex(unsigned int index) const
{
  // take the internal first palette color into account
  const auto adjustedIndex = index + 1u;
  assert(adjustedIndex < static_cast<unsigned int>(paletteColors.size()));
  return paletteColors[adjustedIndex];
}

void ImageModel::setPaletteColorAtIndex(const unsigned int index, const QRgb color)
{
  // take the internal first palette color into account
  const auto adjustedIndex = index + 1u;
  assert(adjustedIndex < static_cast<unsigned int>(paletteColors.size()));
  paletteColors[adjustedIndex] = color;

  for (auto& layer : layers)
  {
    layer->image->setColorTable(paletteColors);
  }

  emit paletteChanged();
}

unsigned int ImageModel::getPaletteColorCount() const
{
  // take the internal first palette color into account
  assert(paletteColors.size() > 0);
  return static_cast<unsigned int>(paletteColors.size()) - 1u;
}

void ImageModel::setSelectedPaletteColorIndex(const unsigned int selectedPaletteColorIndex)
{
  // take the internal first palette color into account
  const auto adjustedIndex = selectedPaletteColorIndex + 1u;
  assert(adjustedIndex < static_cast<unsigned int>(paletteColors.size()));
  this->selectedPaletteColorIndex = adjustedIndex - 1u;

  emit selectedPaletteColorIndexChanged();
}

void ImageModel::addLayer()
{
  auto newLayer = new Layer;
  newLayer->image = std::make_unique<QImage>(width, height, QImage::Format::Format_Indexed8);
  
  // set all indices to the internal first palette color (fully transparent)
  newLayer->image->setColorTable(paletteColors);
  memset(newLayer->image->bits(), 0, newLayer->image->sizeInBytes());

  layers.push_back(std::unique_ptr<Layer>(newLayer));

  setSelectedLayerIndex(static_cast<unsigned int>(layers.size()) - 1u);

  // do not emit the layersChanged signal as adding a transparent layer can not change the image
}

void ImageModel::removeSelectedLayer()
{
  layers.erase(layers.begin() + selectedLayerIndex);

  // emit the layersChanged signal as removing a layer is likely to cause a change in the image
  emit layersChanged();
}

void ImageModel::changeLayerOrder(unsigned int fromIndex, unsigned int toIndex)
{
  if (fromIndex < toIndex)
  // moving a layer down to a lower position in the order
  {
    std::rotate(layers.begin() + fromIndex, layers.begin() + fromIndex + 1, layers.begin() + toIndex);
    
  }
  else
  // moving a layer up to a higher position in the order
  {
    std::rotate(layers.begin() + toIndex, layers.begin() + fromIndex, layers.begin() + fromIndex + 1);
  }

  // emit the layersChanged signal as changing the order of layers is likely to cause a change in the image
  emit layersChanged();
}

QImage* ImageModel::getLayerImage(const unsigned int layerIndex) const
{
  assert(layerIndex < layers.size());
  return layers[layerIndex]->image.get();
}

void ImageModel::setSelectedLayerIndex(const unsigned int selectedLayerIndex)
{
  assert(selectedLayerIndex < layers.size());
  this->selectedLayerIndex = selectedLayerIndex;
}

bool ImageModel::getLayerVisible(const unsigned layerIndex) const
{
  assert(layerIndex < layers.size());
  return layers[layerIndex]->visible;
}

void ImageModel::setLayerVisible(const unsigned layerIndex, const bool visible)
{
  assert(layerIndex < layers.size());
  layers[layerIndex]->visible = visible;

  // emit the layersChanged signal as showing or hiding a layer is likely to cause a change in the image
  emit layersChanged();
}

void ImageModel::drawOnSelectedLayer(const QPoint& point)
{
  assert(selectedLayerIndex < layers.size());
  if (!layers[selectedLayerIndex]->visible)
  {
    return;
  }

  const auto brushModel = toolModel->getBrushModel();

  for (auto y = 0; y < brushModel->getHeight(); ++y)
  {
    for (auto x = 0; x < brushModel->getWidth(); ++x)
    {
      if (!brushModel->getBrushAt(x, y))
      {
        continue;
      }

      const auto i = point.x() + x;
      const auto j = point.y() + y;

      if (i >= 0 && i < width && j >= 0 && j < height)
      {
        // take the internal first palette color into account
        const auto adjustedPaletteColorIndex = getSelectedPaletteColorIndex() + 1u;
        assert(adjustedPaletteColorIndex < static_cast<unsigned int>(paletteColors.size()));

        layers[selectedLayerIndex]->image->scanLine(j)[i] = adjustedPaletteColorIndex;
      }
    }
  }

  const auto imageRect = QRect(point.x(), point.y(), brushModel->getWidth(), brushModel->getHeight());
  emit imageChanged(imageRect);
}