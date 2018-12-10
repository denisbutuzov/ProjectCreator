#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonOpenDir_pressed();
    void on_buttonRun_pressed();

private:
    Ui::MainWindow *ui;
    QString dirName_;
};
