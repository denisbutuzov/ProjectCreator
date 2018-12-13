#pragma once

#include <QMainWindow>
#include <QDir>

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

    void on_table_cellChanged(int row, int column);

private:
    void getRoundDirs(const QString &dirName, const QString &matchStr = "");
    void renameFile(const QString &fileName, const QString &dirName, const QString &matchStr);

private:
    Ui::MainWindow *ui;
    QString dirName_;
    QStringList docCiphers_;
    QString projectCipher_;
};
