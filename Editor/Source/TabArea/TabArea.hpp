#pragma once

#include "Tab.hpp"

class TabArea : public QTabWidget
{
  Q_OBJECT

public:
  TabArea(const BrushModel* brushModel, QWidget* parent = nullptr);

  void newImageTab(const QString& title, unsigned int width, unsigned int height);
  void closeCurrentImageTab();
  void closeAllImageTabs();

  Image* getCurrentImage() const;

private:
  const BrushModel* brushModel;
};