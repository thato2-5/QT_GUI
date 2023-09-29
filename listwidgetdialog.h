#ifndef LISTWIDGETDIALOG_H
#define LISTWIDGETDIALOG_H

#include <QDialog>

class QListWidget;

class ListWidgetDialog : public QDialog
{
  Q_OBJECT

public:
  ListWidgetDialog();

public slots:
  void moveLeft();
  void moveRight();

private:
  QListWidget *leftList;
  QListWidget *rightList;
};

#endif // LISTWIDGETDIALOG_H
