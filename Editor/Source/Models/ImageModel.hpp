#pragma once

#include "ToolModel.hpp"

class ImageModel : public QObject
{
  Q_OBJECT

public:
  ImageModel(const ToolModel* toolModel, unsigned int width, unsigned int height);

  QRgb getPaletteColorAtIndex(const unsigned int index) const;
  void setPaletteColorAtIndex(const unsigned int index, const QRgb color);
  unsigned int getPaletteColorCount() const;
  unsigned int getSelectedPaletteColorIndex() const { return selectedPaletteColorIndex; }
  void setSelectedPaletteColorIndex(const unsigned int selectedPaletteColorIndex);
  QRgb getSelectedPaletteColor() const { return getPaletteColorAtIndex(getSelectedPaletteColorIndex()); }

  unsigned int getLayerCount() const { return static_cast<unsigned int>(layers.size()); }
  void addLayer();
  void removeSelectedLayer();
  void changeLayerOrder(unsigned int fromIndex, unsigned int toIndex);
  QImage* getLayerImage(const unsigned int layerIndex) const;
  unsigned int getSelectedLayerIndex() const { return selectedLayerIndex; };
  void setSelectedLayerIndex(const unsigned int selectedLayerIndex);

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void drawOnSelectedLayer(const QPoint& point);

signals: 
  void paletteChanged();
  void selectedPaletteColorIndexChanged();
  void layersChanged();
  void imageChanged(const QRect& imageRect);

private:
  const ToolModel* toolModel;

  QVector<QRgb> paletteColors;
  unsigned int selectedPaletteColorIndex;

  std::vector<std::unique_ptr<QImage>> layers;
  unsigned int selectedLayerIndex; // not including internal first palette color

  int width, height;
};