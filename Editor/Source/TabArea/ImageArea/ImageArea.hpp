#pragma once

#include "Image.hpp"

class ImageArea : public QScrollArea
{
  Q_OBJECT

public:
  ImageArea(ImageModel* imageModel, const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return image; }

private:
  // memory managed by Qt
  Image* image;
};