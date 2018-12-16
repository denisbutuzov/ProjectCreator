#pragma once

#include <QMap>
#include <QObject>

#ifdef WINDOWS
   #define SEPARATOR "\\"
#else
   #define SEPARATOR "/"
#endif

class Renamer
        : public QObject
{
    Q_OBJECT

public:
    Renamer(const QString &rootDir,
            const QString &projectCipher,
            const QMap<QString, QString> &inventoryNumbers);
    void run();

signals:
    void renamed(const QString &oldName, const QString &newName);
    void noRenamed(const QString &name);

private:
    void findDirs();
    void renameDirs();
    void renameFiles();
    void renameFilesInDir(const QString &doc, const QString &dirName);
    void attemptToRename(const QString &oldName, const QString &newName);

private:
    QString rootDir_;
    QString projectCipher_;
    QMap<QString, QString> inventoryNumbers_;
    QMap<QString, QString> dirs_;
};
