#include "cvirtualport.h"

#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/csynthpro.h"
#include "control/cwire.h"
#include "factory/qtfactory.h"
#include "presentation/pvirtualport.h"

CVirtualPort::CVirtualPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
{
}

Port* CVirtualPort::replicate()
{
    CPort* cPort = dynamic_cast<CPort*>(VirtualPort::replicate());
    presentation()->addReplication(cPort->presentation());
    return cPort;
}

bool CVirtualPort::removePort(Port* port)
{
    CPort* cPort = dynamic_cast<CPort*>(port);
    if (VirtualPort::removePort(cPort)) {
        // TODO Remove replication
        // presentation()->removeReplication(cPort->presentation());
        // cPort->deleteLater();
        return true;
    }
    return false;
}

void CVirtualPort::setPresentation(PVirtualPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
}

void CVirtualPort::updateWiresPositions()
{
    foreach (Port* port, connections()) {
        CPort* cPort = dynamic_cast<CPort*>(port);
        if (cPort->wire()) {
            cPort->wire()->updatePosition();
        }
    }
}

void CVirtualPort::showCompatibleFeedback(CVirtualPort* from)
{
    if (from != this) {
        foreach (Port* port, connections()) {
            CPort* cPort = dynamic_cast<CPort*>(port);
            cPort->showFeedback(compatible(from));
        }
    }
}

void CVirtualPort::hideFeedback()
{
    foreach (Port* port, connections()) {
        CPort* cPort = dynamic_cast<CPort*>(port);
        cPort->hideFeedback();
    }
}
