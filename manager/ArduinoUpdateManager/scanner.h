#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <QString>
#include <QByteArray>
#include <QVector>
#include <QStack>
#include <QDir>
#include "manager.h"

class Scanner
{
public:
    Scanner();
    void scan(ReleaseFileList &r, const QString &directory);
protected:
    void scanRecursive(QDir &d, ReleaseFileList &r, QStack<QString> &dirname);
    QByteArray hashFile(QFile&);
};

#endif
