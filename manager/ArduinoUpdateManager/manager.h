#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <QString>
#include <QByteArray>
#include <QVector>
#include <QHash>
#include <QtXml/QDomDocument>
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

struct OSRelease
{
    QString name;
    ReleaseFileList files;
    QString parent;
};

typedef QVector<OSRelease> OSReleaseList;

typedef QHash<QString, OSReleaseList> AllReleaseList;

class Manager
{
public:
    bool exists(const ReleaseFile &f) const ;
    void add   (const ReleaseFile &f);
    const OSReleaseList &getReleaseList(const QString &os) const;
    void updateReleasesFromXML(QDomElement release);
    void saveReleasesToXML(QDomDocument doc, QDomElement rl);
private:
    /* Fast list with all hashes */
    QHash<SHA,quint32> m_shaMap;
    /* Ordered resources */
    QVector<SHA> m_resources;
    AllReleaseList m_releaseList;
};

#endif
