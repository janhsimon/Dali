#pragma once

#include "ImageTab.hpp"

class ImageArea : public QTabWidget
{
  Q_OBJECT

public:
  ImageArea(QWidget* parent = nullptr);

  Image* getCurrentImage() const;
};