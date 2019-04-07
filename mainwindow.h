#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QMap>

#include "renamer.h"

namespace Ui {
class MainWindow;
}

class MainWindow
        : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonOpenDir_pressed();
    void on_buttonRun_pressed();
    void on_tableDocs1_cellChanged(int row, int column);
    void on_tableDocs2_cellChanged(int row, int column);
    void on_tableDocs3_cellChanged(int row, int column);
    void on_tableDocs4_cellChanged(int row, int column);
    void on_successfulRename(const QString &oldName, const QString &newName);
    void on_failedRename(const QString &name);
    void on_lineEditProjectCipher_textChanged(const QString &arg1);

private:
    void setupTable(QTableWidget *table);
    void addInventoryNumberToMap(QTableWidget *table, int row, int column);
    void checkForRun();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> inventoryNumbers_;
    Renamer *renamer_;
};
