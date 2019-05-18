#include "LayerListItem.hpp"

#include <iostream>

LayerListItem::LayerListItem(const QString& layerName, ImageModel* imageModel, QListWidget* listWidget) :
  QWidget(listWidget),
  imageModel(imageModel),
  listWidget(listWidget)
{
  setObjectName("LayerListItem");

  const auto rootLayout = new QHBoxLayout();
  rootLayout->setContentsMargins(2, 2, 2, 2);

  const auto iconLabel = new QLabel(this);
  iconLabel->setPixmap(QIcon(":Icons/Layer.svg").pixmap(16, 16));
  rootLayout->addWidget(iconLabel);

  layerNameLineEdit = new QLineEdit(layerName, this);
  layerNameLineEdit->setFrame(false);
  layerNameLineEdit->setEnabled(false);
  rootLayout->addWidget(layerNameLineEdit);

  rootLayout->addStretch();

  const auto buttonsLayout = new QHBoxLayout();
  buttonsLayout->setContentsMargins(0, 0, 0, 0);

  const auto renameButton = new QPushButton(this);
  renameButton->setIcon(QIcon(":Icons/Rename.svg"));
  renameButton->setFixedSize(16, 16);
  buttonsLayout->addWidget(renameButton);

  const auto visibilityCheckbox = new QCheckBox(this);
  visibilityCheckbox->setChecked(true);
  buttonsLayout->addWidget(visibilityCheckbox);

  rootLayout->addLayout(buttonsLayout);

  setLayout(rootLayout);

  connect(layerNameLineEdit, &QLineEdit::editingFinished, this, [&]()
  {
    layerNameLineEdit->setEnabled(false);
  });

  connect(renameButton, &QPushButton::clicked, this, [&]()
  {
    layerNameLineEdit->selectAll();
    QTimer::singleShot(0, layerNameLineEdit, SLOT(setFocus())); // needed to ensure that focus is correctly set
    layerNameLineEdit->setEnabled(true);
  });

  connect(visibilityCheckbox, &QCheckBox::toggled, this, [&](bool checked)
  {
    for (int i = 0; i < this->listWidget->count(); ++i)
    {
      const auto item = this->listWidget->item(i);
      const auto itemWidget = this->listWidget->itemWidget(item);

      if (itemWidget == this)
      {
        this->imageModel->setLayerVisible(i, checked);
        return;
      }
    }
  });
}