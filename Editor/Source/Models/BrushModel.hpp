#pragma once

#include <QtWidgets>

class BrushModel : public QObject
{
  Q_OBJECT

public:
  BrushModel();

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  bool getBrushAt(const int x, const int y) const;
  void setBrushAt(const int x, const int y, const int value);

  QImage* getBrushImage() const { return brush.get(); }

signals:
  void brushChanged();

private:
 QVector<QRgb> colors;
 std::unique_ptr<QImage> brush;
 int width, height;
};