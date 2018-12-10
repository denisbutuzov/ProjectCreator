#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->buttonRun->setDisabled(true);
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
    QDir dir(dirName_);
    QFileInfoList info = dir.entryInfoList(QDir::Files);
    int count = 0;
    for(const auto &fileInfo : info)
    {
        QFile::rename(fileInfo.absoluteFilePath(),
                      fileInfo.absolutePath() + "/" + QString::number(++count) + ".txt");
    }
}
