#pragma once

#include "../../Models/ImageModel.hpp"

class SideBar : public QWidget
{
  Q_OBJECT

public:
  SideBar(ImageModel* imageModel, QWidget* parent = nullptr);
};