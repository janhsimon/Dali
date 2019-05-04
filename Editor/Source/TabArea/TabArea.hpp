#pragma once

#include "Tab.hpp"

class TabArea : public QTabWidget
{
  Q_OBJECT

public:
  TabArea(QWidget* parent = nullptr);

  void newImageTab(BrushModel* brushModel, const QString& title, unsigned int width, unsigned int height);
  void closeCurrentImageTab();
  void closeAllImageTabs();

  Image* getCurrentImage() const;
};