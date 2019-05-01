#pragma once

#include "Image.hpp"

class ImageArea : public QScrollArea
{
  Q_OBJECT

public:
  ImageArea(const BrushModel* brushModel, unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return image.get(); }

private:
  std::unique_ptr<Image> image;
};