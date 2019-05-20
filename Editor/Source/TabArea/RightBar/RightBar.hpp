#pragma once

#include "../../Models/ImageModel.hpp"

class RightBar : public QWidget
{
  Q_OBJECT

public:
  RightBar(ImageModel* imageModel, QWidget* parent = nullptr);

private:
  static constexpr auto WIDTH = 300;
};