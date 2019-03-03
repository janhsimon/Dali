#pragma once

#include "Image.hpp"

class ImageTab : public QScrollArea
{
  Q_OBJECT

public:
  ImageTab(QWidget* parent = nullptr);

  Image* getImage() const { return image.get(); }

private:
  std::unique_ptr<Image> image;
};