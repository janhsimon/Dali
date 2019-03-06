#pragma once

#include "ImageTab.hpp"

class MainArea : public QTabWidget
{
  Q_OBJECT

public:
  MainArea(QWidget* parent = nullptr);

  void newImageTab(const QString& title, unsigned int width, unsigned int height);
  void closeCurrentImageTab();
  void closeAllImageTabs();

  Image* getCurrentImage() const;
};