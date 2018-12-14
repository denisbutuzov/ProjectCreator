#include <QFileInfo>
#include <QRegularExpression>
#include <QDir>

#include <QDebug>

#include "renamer.h"

Renamer::Renamer(const QString &rootDir, const QStringList &docs)
    : rootDir_(rootDir)
    , docs_(docs)
{

}

void Renamer::run()
{
    findDirs();
}

void Renamer::findDirs()
{
    QFileInfoList dirsInfo = QDir(rootDir_).entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(const auto &dirInfo : dirsInfo)
    {
        for(const auto &doc : docs_)
        {
            QRegularExpressionMatch match = QRegularExpression(doc).match(dirInfo.fileName());
            if(match.hasMatch())
            {
                dirs_.push_back(dirInfo.fileName());
            }
        }
    }
}

void Renamer::printDirs()
{
    for(const auto &dir : dirs_)
    {
        qDebug() << dir;
    }
}

//void Renamer::getRoundDirs(const QString &dirName, const QString &matchStr)
//{
//    QFileInfoList info = QDir(dirName).entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
//    for(const auto &fileInfo : info)
//    {
//        if(fileInfo.isDir())
//        {
//            for(const auto &docCipher : inventoryNumbers_)
//            {
//                QRegularExpressionMatch match = QRegularExpression(docCipher).match(fileInfo.fileName());
//                if(match.hasMatch())
//                {
//                    getRoundDirs(fileInfo.absoluteFilePath(), docCipher);
//                }
//            }
//        }
//        else if(!matchStr.isEmpty())
//        {
//            rename(fileInfo.fileName(), fileInfo.absolutePath(), matchStr);
//        }
//    }
//}

//void Renamer::rename(const QString &fileName, const QString &dirName, const QString &matchStr)
//{
//    QRegularExpressionMatch match = QRegularExpression(matchStr).match(fileName);
//    if(match.hasMatch())
//    {
//        QFile::rename(dirName + "/" + fileName, dirName + "/1.txt");
//    }
//}
