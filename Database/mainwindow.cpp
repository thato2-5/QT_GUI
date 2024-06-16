/*
* File : mainwindow.cpp
* Author: Thato Monyamane
* Description: This database class can perform DML operations such as inserting and querying data using sqlite3
* Date: 03/08/2023
* Version: 1.00
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createDatabaseConnection();
    displayDataFromDatabase();  // Show data on startup
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDatabaseConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users_details.db");

    if (!db.open())
    {
        QMessageBox::critical(this, "Error", "Failed to open database");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT)");
}

bool MainWindow::insertDataIntoDatabase(const QString &name, const QString &email)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (name, email) VALUES (:name, :email)");
    query.bindValue(":name", name);
    query.bindValue(":email", email);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed to insert data: " + query.lastError().text());
        return false;
    }

    return true;
}

QList<QStringList> MainWindow::displayDataFromDatabase()
{
    QList<QStringList> result;

    QSqlQuery query("SELECT * FROM users");
    while (query.next())
    {
        QStringList rowData;
        rowData << query.value(0).toString() //id
                << query.value(1).toString() // name
                << query.value(2).toString(); //email
        result.append(rowData);
    }

    return result;
}

bool MainWindow::updateDataInDatabase(int id, const QString &name, const QString &email)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET name = :name, email = :email WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed to update data: " + query.lastError().text());
        return false;
    }

    return true;
}

bool MainWindow::deleteDataFromDatabase(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed to delete data: " + query.lastError().text());
        return false;
    }

    return true;
}

void MainWindow::on_addButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    QString email = ui->emailLineEdit->text();

    if (insertDataIntoDatabase(name, email))
    {
        QMessageBox::information(this, "Success", "Details added successfully");
        displayDataFromDatabase();
    }
}


void MainWindow::on_displayButton_clicked()
{
    QList<QStringList> data = displayDataFromDatabase();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(data.size());
    int row = 0;
    for (const QStringList &rowData : data)
    {
        int col = 0;
        for (const QString &value : rowData)
        {
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(row, col, item);
            col++;
        }
        row++;
    }
}

