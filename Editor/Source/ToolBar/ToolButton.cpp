#include "ToolButton.hpp"

ToolButton::ToolButton(const QString& toolTip, const QIcon& icon, const QKeySequence& shortcut, QWidget* parent) :
  QPushButton(parent)
{
  setFixedSize(QSize(BUTTON_SIZE, BUTTON_SIZE));

  setToolTip(toolTip + " (" + shortcut.toString() + ")");

  setShortcut(shortcut);

  setIcon(icon);
  setIconSize(QSize(ICON_SIZE, ICON_SIZE));
}

ToolButton::ToolButton(const QString& toolTip, const QIcon& icon, const QKeySequence& shortcut, QButtonGroup* buttonGroup, QWidget* parent, bool checked) :
  ToolButton(toolTip, icon, shortcut, parent)
{
  setCheckable(true);
  setChecked(checked);

  buttonGroup->addButton(this);
}