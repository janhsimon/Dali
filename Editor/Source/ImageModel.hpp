#pragma once

#include <QtWidgets>

class ImageModel : public QObject
{
  Q_OBJECT

public:
  ImageModel(unsigned int width, unsigned int height);

  unsigned int getPaletteColorAtIndex(unsigned int index) const { return paletteColors[index]; }
  void setPaletteColorAtIndex(const unsigned int index, const QRgb color);
  unsigned int getPaletteColorCount() const { return paletteColors.size(); }

  QImage* getImage() const { return image.get(); }
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  QRect setPixels(const QPoint point);

signals: 
  void paletteChanged(int index);
  void pixelsChanged();

private:
  QVector<QRgb> paletteColors;
  std::unique_ptr<QImage> image;
  int width, height;
};