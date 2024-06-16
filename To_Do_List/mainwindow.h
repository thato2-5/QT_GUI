#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include <QAction>
#include <QMessageBox>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void removeCompletedTasks();
    void toggleTaskCompletion(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    QList<Task> tasks;
    int tasks_number;
};
#endif // MAINWINDOW_H
