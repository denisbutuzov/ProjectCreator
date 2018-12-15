#include <QFileDialog>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(560, 560);

    ui->buttonRun->setDisabled(true);
    ui->lineEditDir->setReadOnly(true);

    setupTable(ui->tableDocs1);
    setupTable(ui->tableDocs2);
    setupTable(ui->tableDocs3);
    setupTable(ui->tableDocs4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpenDir_pressed()
{
    QString tempDirName = QFileDialog::getExistingDirectory(this, tr("Выберите директорию"));
    if(!tempDirName.isEmpty())
    {
        ui->lineEditDir->setText(tempDirName);
    }

    checkForRun();
}

void MainWindow::on_buttonRun_pressed()
{
    renamer_ = new Renamer(ui->lineEditDir->text(),
                           ui->lineEditProjectCipher->text(),
                           inventoryNumbers_);

    connect(renamer_, SIGNAL(renamed(const QString &, const QString &)),
            this, SLOT(on_successfulRename(const QString &, const QString &)));
    connect(renamer_, SIGNAL(noRenamed(const QString &)),
            this, SLOT(on_failedRename(const QString &)));
    renamer_->run();
}

void MainWindow::setupTable(QTableWidget *table)
{
    table->setColumnWidth(0, 150);
    table->setSelectionMode(QAbstractItemView::NoSelection);
}

void MainWindow::addInventoryNumberToMap(QTableWidget *table, int row, int column)
{
    static const QMap<QString, QString> trMap
    {
        {"С0", "S0"}, {"С2", "S2"}, {"П2", "P2"}, {"П3", "P3"},
        {"ЭД", "ED"}, {"ПМ", "PM"}, {"Ф0", "F0"}, {"ПВ", "PV"},
        {"И3", "I3"}, {"В1", "V1"}, {"В2", "V2"}, {"П5", "P5"},
        {"П7", "P7"}, {"С9", "S9"}, {"ПА", "PA"}, {"ПБ", "PB"}
    };

    QString cellString = table->item(row, column)->text();
    if(!cellString.isEmpty())
    {
        inventoryNumbers_.insert(trMap[table->verticalHeaderItem(row)->text()], cellString);
    }
    else
    {
        inventoryNumbers_.remove(trMap[table->verticalHeaderItem(row)->text()]);
    }

    checkForRun();
}

void MainWindow::checkForRun()
{
    if(!ui->lineEditDir->text().isEmpty()
            && !inventoryNumbers_.isEmpty()
            && !ui->lineEditProjectCipher->text().isEmpty())
    {
        ui->buttonRun->setDisabled(false);
    }
    else
    {
        ui->buttonRun->setDisabled(true);
    }
}

void MainWindow::on_tableDocs1_cellChanged(int row, int column)
{
    addInventoryNumberToMap(dynamic_cast<QTableWidget *>(sender()), row, column);
}

void MainWindow::on_tableDocs2_cellChanged(int row, int column)
{
    addInventoryNumberToMap(dynamic_cast<QTableWidget *>(sender()), row, column);
}

void MainWindow::on_tableDocs3_cellChanged(int row, int column)
{
    addInventoryNumberToMap(dynamic_cast<QTableWidget *>(sender()), row, column);
}

void MainWindow::on_tableDocs4_cellChanged(int row, int column)
{
    addInventoryNumberToMap(dynamic_cast<QTableWidget *>(sender()), row, column);
}

void MainWindow::on_successfulRename(const QString &oldName, const QString &newName)
{
    QString time = QTime::currentTime().toString();
    ui->textEdit->append(time + " [SUCCESS]: " + oldName + " --> " + newName);
    ui->textEdit->append("");
}

void MainWindow::on_failedRename(const QString &name)
{
    QString time = QTime::currentTime().toString();
    ui->textEdit->append(time + "[ERROR]: can't renamed the file/folder -- " + name);
    ui->textEdit->append("");
}


void MainWindow::on_lineEditProjectCipher_textChanged(const QString &arg1)
{
    checkForRun();
}
