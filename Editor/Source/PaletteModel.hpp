#pragma once

#include <QtWidgets>

class PaletteModel : public QObject
{
  Q_OBJECT

public:
  PaletteModel();

  void setColorAtIndex(const unsigned int index, const QRgb color);

  QVector<QRgb> getPaletteColors() const { return paletteColors; }

signals:
  void paletteChanged();

private:
  QVector<QRgb> paletteColors;
};