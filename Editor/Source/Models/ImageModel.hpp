#pragma once

#include "ToolModel.hpp"

struct Layer
{
  std::unique_ptr<QImage> image;
  bool visible;
};

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
  bool getLayerVisible(const unsigned layerIndex) const;
  void setLayerVisible(const unsigned layerIndex, const bool visible);

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void setPixel(const unsigned int layerIndex, const int x, const int y, const unsigned int paletteColorIndex); // emit imageChanged when done changing pixels

  QRect getDirtyRect() const { return dirtyRect; }
  void setDirtyRect(const QRect& dirtyRect) { this->dirtyRect = dirtyRect; }

signals: 
  void paletteChanged();
  void selectedPaletteColorIndexChanged();
  void layersChanged();
  void imageChanged(const QRect& imageRect);

private:
  // non-owning
  const ToolModel* toolModel;

  QVector<QRgb> paletteColors;
  unsigned int selectedPaletteColorIndex;

  std::vector<std::unique_ptr<Layer>> layers;
  unsigned int selectedLayerIndex; // not including internal first palette color

  int width, height;

  QRect dirtyRect;
};