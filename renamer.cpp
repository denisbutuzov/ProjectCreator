#include <QFileInfo>
#include <QRegularExpression>
#include <QDir>

#include "renamer.h"

Renamer::Renamer(const QString &rootDir,
                 const QString &projectCipher,
                 const QMap<QString, QString> &inventoryNumbers)
    : rootDir_(rootDir)
    , projectCipher_(projectCipher)
    , inventoryNumbers_(inventoryNumbers)
{
}

void Renamer::run()
{
    findDirs();
    renameDirs();
    renameFiles();

    delete this;
}

void Renamer::findDirs()
{
    QFileInfoList dirsInfo = QDir(rootDir_).entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(const auto &dirInfo : dirsInfo)
    {
        for(const auto &doc : inventoryNumbers_.keys())
        {
            QRegularExpressionMatch match = QRegularExpression(doc).match(dirInfo.fileName());
            if(match.hasMatch())
            {
                dirs_.insert(doc, dirInfo.absoluteFilePath());
            }
        }
    }
}

void Renamer::renameDirs()
{
    auto dirIter = dirs_.begin();
    for(auto dirIter = dirs_.begin(); dirIter != dirs_.end(); dirIter++)
    {
        QString oldName = dirIter.value();
        QString newName = dirIter.value().replace(QRegularExpression("№\\d+(?=_)"), "№" + inventoryNumbers_[dirIter.key()])
                                         .replace(QRegularExpression("_.+(?=-" + dirIter.key() + ")"), "_" + projectCipher_);
        if(oldName != newName)
        {
            attemptToRename(oldName, newName);
        }
    }
}

void Renamer::renameFiles()
{
    auto dirIter = dirs_.begin();
    for(auto dirIter = dirs_.begin(); dirIter != dirs_.end(); dirIter++)
    {
        renameFilesInDir(dirIter.key(), dirIter.value());
    }
}

void Renamer::renameFilesInDir(const QString &doc, const QString &dirName)
{
    QFileInfoList info = QDir(dirName).entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    for(const auto &fileInfo : info)
    {
        if(fileInfo.isDir())
        {
            renameFilesInDir(doc, fileInfo.absoluteFilePath());
        }
        else
        {
            QRegularExpressionMatch match = QRegularExpression(doc).match(fileInfo.fileName());
            if(match.hasMatch())
            {
                QString oldName = fileInfo.absoluteFilePath();
                QString newName = fileInfo.absolutePath() + "/" + fileInfo.fileName().replace(QRegularExpression("^.+(?=-" + doc + ")"), projectCipher_);
                if(oldName != newName)
                {
                    attemptToRename(oldName, newName);
                }
            }
        }
    }
}

void Renamer::attemptToRename(const QString &oldName, const QString &newName)
{
    if(QFile::rename(oldName, newName))
    {
        emit renamed(oldName, newName);
    }
    else
    {
        emit noRenamed(oldName);
    }
}
