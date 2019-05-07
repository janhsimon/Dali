#pragma once

#include "ImageArea/ImageArea.hpp"

class Tab : public QWidget
{
  Q_OBJECT

public:
  Tab(const ToolModel* toolModel, unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return imageArea->getImage(); }

private:
  std::unique_ptr<ImageArea> imageArea;
};