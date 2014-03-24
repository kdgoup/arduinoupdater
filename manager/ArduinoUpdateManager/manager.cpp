#include "manager.h"


bool Manager::exists(const ReleaseFile &f) const
{
    return m_shaMap.contains(f.sha);
}

void Manager::add(const ReleaseFile &f)
{
    m_shaMap[f.sha] = true;
}
