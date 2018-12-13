#include <QFileDialog>
#include <QRegularExpression>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->buttonRun->setDisabled(true);


    docCiphers_ << "V2" << "V1" << "P7";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpenDir_pressed()
{
    dirName_ = QFileDialog::getExistingDirectory(this, tr("Выберите директорию"));
    if(dirName_.isEmpty())
    {
        ui->buttonRun->setDisabled(true);
    }
    else
    {
        ui->buttonRun->setEnabled(true);
    }
}

void MainWindow::on_buttonRun_pressed()
{
    getRoundDirs(dirName_);
}

void MainWindow::getRoundDirs(const QString &dirName, const QString &matchStr)
{
    QFileInfoList info = QDir(dirName).entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    for(const auto &fileInfo : info)
    {
        if(fileInfo.isDir())
        {
            for(const auto &docCipher : docCiphers_)
            {
                QRegularExpressionMatch match = QRegularExpression(docCipher).match(fileInfo.fileName());
                if(match.hasMatch())
                {
                    getRoundDirs(fileInfo.absoluteFilePath(), docCipher);
                }
            }
        }
        else if(!matchStr.isEmpty())
        {
            renameFile(fileInfo.fileName(), fileInfo.absolutePath(), matchStr);
        }
    }
}

void MainWindow::renameFile(const QString &fileName, const QString &dirName, const QString &matchStr)
{
    QRegularExpressionMatch match = QRegularExpression(matchStr).match(fileName);
    if(match.hasMatch())
    {
        QFile::rename(dirName + "/" + fileName, dirName + "/1.txt");
    }
}

void MainWindow::on_table_cellChanged(int row, int column)
{
    QTableWidgetItem *item = ui->table->item(row, column);
    qDebug() << item->text();
}
