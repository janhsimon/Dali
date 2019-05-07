#pragma once

#include <QtWidgets>

class ToolButton : public QPushButton
{
  Q_OBJECT

public:
  ToolButton(const QString& toolTip, const QIcon& icon, const QKeySequence& shortcut, QWidget* parent = nullptr);
  ToolButton(const QString& toolTip, const QIcon& icon, const QKeySequence& shortcut, QButtonGroup* buttonGroup, QWidget* parent = nullptr, bool checked = false);

private:
  static constexpr auto BUTTON_SIZE = 48;
  static constexpr auto ICON_SIZE = 32;
};