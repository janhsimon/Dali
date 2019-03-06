#pragma once

#include "Image.hpp"

class ImageScrollArea : public QScrollArea
{
  Q_OBJECT

public:
  ImageScrollArea(unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return image.get(); }

private:
  std::unique_ptr<Image> image;
};