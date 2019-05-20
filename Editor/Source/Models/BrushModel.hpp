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
  void setBrushAt(const int x, const int y, const bool value);
  void setColor(const QRgb color);

  QImage* getBrushImage() const { return brush.get(); }

signals:
  //void brushChanged();
  void colorChanged();

private:
  // owning
  std::unique_ptr<QImage> brush;
  
  QVector<QRgb> colors;
  int width, height;
};