#pragma once

#include <QtWidgets>

class ImageModel : public QObject
{
  Q_OBJECT

public:
  ImageModel(unsigned int width, unsigned int height);

  QRgb getPaletteColorAtIndex(const unsigned int index) const;
  void setPaletteColorAtIndex(const unsigned int index, const QRgb color);
  unsigned int getPaletteColorCount() const;
  unsigned int getSelectedPaletteColorIndex() const { return selectedPaletteColorIndex; }
  void setSelectedPaletteColorIndex(const unsigned int selectedPaletteColorIndex);

  unsigned int getLayerCount() const { return static_cast<unsigned int>(layers.size()); }
  void addLayer();
  void removeSelectedLayer();
  void changeLayerOrder(unsigned int fromIndex, unsigned int toIndex);
  QImage* getLayerImage(const unsigned int layerIndex) const { return layers[layerIndex].get(); }
  unsigned int getSelectedLayerIndex() const { return selectedLayerIndex; };
  void setSelectedLayerIndex(const unsigned int selectedLayerIndex) { this->selectedLayerIndex = selectedLayerIndex; }

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void drawOnSelectedLayer(const QPoint point);

signals: 
  void paletteChanged();
  void selectedPaletteColorIndexChanged();
  void layersChanged();
  void imageChanged(const QRect& imageRect);

private:
  QVector<QRgb> paletteColors;
  unsigned int selectedPaletteColorIndex;

  std::vector<std::unique_ptr<QImage>> layers;
  unsigned int selectedLayerIndex;

  int width, height;
};