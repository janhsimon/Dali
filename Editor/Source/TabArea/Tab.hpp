#pragma once

#include "Image/ImageScrollArea.hpp"

class Tab : public QWidget
{
  Q_OBJECT

public:
  Tab(unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return imageScrollArea->getImage(); }

private:
  std::unique_ptr<ImageScrollArea> imageScrollArea;
};