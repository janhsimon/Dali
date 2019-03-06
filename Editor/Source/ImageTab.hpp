#pragma once

#include "ImageScrollArea.hpp"

class ImageTab : public QWidget
{
  Q_OBJECT

public:
  ImageTab(unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return imageScrollArea->getImage(); }

private:
  std::unique_ptr<ImageScrollArea> imageScrollArea;
};