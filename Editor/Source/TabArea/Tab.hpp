#pragma once

#include "ImageArea/ImageArea.hpp"
#include "LeftBar/LeftBar.hpp"
#include "RightBar/RightBar.hpp"

class Tab : public QWidget
{
  Q_OBJECT

public:
  Tab(unsigned int width, unsigned int height, QWidget* parent = nullptr);

  Image* getImage() const { return imageArea->getImage(); }
  ImageModel* getImageModel() const { return imageModel.get(); }
  ToolModel* getToolModel() const { return toolModel.get(); }

private:
  // owning
  std::unique_ptr<ImageModel> imageModel;
  std::unique_ptr<ToolModel> toolModel;

  // memory managed by Qt
  LeftBar* leftBar;
  ImageArea* imageArea;
  RightBar* rightBar;
};