#pragma once

#include <QStringList>

class Renamer
{
public:
    Renamer(const QString &rootDir, const QStringList &docs);
    void run();
    void printDirs();

private:
    void findDirs();


//    void getRoundDirs(const QString &dirName, const QString &matchStr = "");
//    void rename(const QString &fileName, const QString &dirName, const QString &matchStr);

private:
    QString rootDir_;
    QStringList docs_;

//    QString projectCipher_;
//    QStringList inventoryNumbers_;
};
