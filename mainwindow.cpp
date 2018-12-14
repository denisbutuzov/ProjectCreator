#include  <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditDir->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpenDir_pressed()
{
    QString tempDirName = QFileDialog::getExistingDirectory(this, tr("Выберите директорию"));
    if(tempDirName.isEmpty())
    {
        //
    }
    else
    {
        ui->lineEditDir->setText(tempDirName);
    }
}

void MainWindow::on_buttonRun_pressed()
{
    QStringList list = {"V2", "V1", "SR"};

    renamer_ = new Renamer(ui->lineEditDir->text(), list);
    renamer_->run();
    renamer_->printDirs();
}
