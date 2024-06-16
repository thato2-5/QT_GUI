#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>

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
    void on_addButton_clicked();

    void on_displayButton_clicked();

private:
    Ui::MainWindow *ui;

    void createDatabaseConnection();
    bool insertDataIntoDatabase(const QString &name, const QString &email);
    QList<QStringList> displayDataFromDatabase();
    bool updateDataInDatabase(int id, const QString &name, const QString &email);
    bool deleteDataFromDatabase(int id);
};
#endif // MAINWINDOW_H
