#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <QString>
#include <QByteArray>
#include <QVector>
#include <QHash>

#include <cassert>

typedef QByteArray SHA;

struct ReleaseFile
{
    QString name;
    SHA sha;
    bool exec;
    qint64 size;
};

typedef QVector<ReleaseFile> ReleaseFileList;

class Manager
{
public:
    bool exists(const ReleaseFile &f) const ;
    void add   (const ReleaseFile &f);
private:
    /* Fast list with all hashes */
    QHash<SHA,bool> m_shaMap;
};

#endif
