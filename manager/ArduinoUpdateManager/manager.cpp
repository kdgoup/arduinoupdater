#include "manager.h"
#include <QDomElement>
#include <cassert>


bool Manager::exists(const ReleaseFile &f) const
{
    return m_shaMap.contains(f.sha);
}

void Manager::add(const ReleaseFile &f)
{
    m_shaMap[f.sha] = true;
}

const OSReleaseList &Manager::getReleaseList(const QString &os) const
{
    return m_releaseList.find(os).value();
}

void Manager::updateReleasesFromXML(QDomElement rl)
{
    QDomElement r;
    m_releaseList.clear();

    for (; !r.isNull(); r = r.nextSiblingElement("Release")) {
        QString osname = r.attribute("os");
        //assert();

    }
}

void Manager::saveReleasesToXML(QDomDocument doc, QDomElement rl)
{
    foreach (const QString &os, m_releaseList.keys()) {
        foreach (const OSRelease &osrl, m_releaseList[os]) {
            QDomElement r = doc.createElement("Release");
            r.attribute("os")=os;
            rl.appendChild(r);
            if (osrl.parent.size()) {
                r.attribute("parent")=osrl.parent;
            }
            // Files...
            QDomElement files = doc.createElement("Files");
            foreach (const ReleaseFile &f, osrl.files) {
                QDomElement file=doc.createElement("File");
                file.attribute("sha") = f.sha;
                file.attribute("target") = f.name;
                file.attribute("size") = f.size;
                if (f.exec)
                    file.attribute("exec") = "true";
            }
        }
    }
}
