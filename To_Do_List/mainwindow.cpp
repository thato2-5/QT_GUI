/*
* File: mainwindow.cpp
* Author: Thato Monyamane
* Description: This class represents a ToDo list which can be populated with tasks as well as the tasks can also be deleted.
* Date: 06/08/2023
* Version: 1.00
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addPushButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &MainWindow::removeCompletedTasks);
    connect(ui->taskListWidget, &QListWidget::itemClicked, this, &MainWindow::toggleTaskCompletion);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    QString taskDescription = ui->taskTextEdit->text().trimmed();
    if (!taskDescription.isEmpty())
    {
        Task task(taskDescription, false);
        tasks.append(task);
        ui->taskListWidget->addItem(taskDescription);
        ui->taskTextEdit->clear();
        tasks_number = ui->taskListWidget->count();
        ui->spinBox->setRange(0, tasks_number);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Please enter a task");
        ui->taskTextEdit->setFocus();
    }

}

void MainWindow::removeCompletedTasks()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow >= 0 && currentRow < tasks.size())
    {
        tasks.removeAt(currentRow);
        delete ui->taskListWidget->takeItem(currentRow);
        tasks_number = ui->taskListWidget->count();
        ui->spinBox->setRange(0, tasks_number);
    }
}

void MainWindow::toggleTaskCompletion(QListWidgetItem *item)
{
    int currentRow = ui->taskListWidget->row(item);
    if (currentRow >= 0 && currentRow < tasks.size())
    {
        Task &task = tasks[currentRow];
        bool isCompleted = task.isCompleted();
        task.setCompleted(!isCompleted);

        // Update the list item text to show completion status
        QString description = task.getDescription();
        if (isCompleted)
            description.prepend("[ ] ");
        else
            description.prepend("[X] ");
        item->setText(description);
    }
}
