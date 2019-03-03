#pragma once

#include "ImageArea.hpp"

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* parent = nullptr);

private:
  std::unique_ptr<ImageArea> imageArea;
};
