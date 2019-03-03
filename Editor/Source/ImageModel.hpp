#pragma once

#include "PaletteModel.hpp"

class ImageModel : public QObject
{
  Q_OBJECT

public:
  ImageModel(unsigned int width, unsigned int height, const PaletteModel* paletteModel);

  QRect setPixels(int x, int y);

  QImage* getImage() const { return image.get(); }
  int getWidth() const { return width; }
  int getHeight() const { return height; }

signals: 
  void pixelsChanged();

private:
  std::unique_ptr<QImage> image;
  int width, height;
};