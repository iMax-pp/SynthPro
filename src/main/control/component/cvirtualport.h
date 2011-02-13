#ifndef CVIRTUALPORT_H
#define CVIRTUALPORT_H

#include "abstraction/component/virtualport.h"

#include <QMap>

class PVirtualPort;
class CPort;
class QtFactory;

class CVirtualPort : public virtual VirtualPort {
    Q_OBJECT

public:
    CVirtualPort(Module* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);

    void initialize();

    void setPresentation(PVirtualPort*);
    inline PVirtualPort* presentation() const { return m_presentation; }

    Connection* connect(VirtualPort* other);
    void disconnect(CPort*);
    // bool disconnect(Connection*);
    // bool reconnect(Connection*, VirtualPort* other);

    void updateWiresPositions();

    void updateAvailableFeedback();

    /**
     * Show feedback, called when drawing a wire from a port.
     * @param The origin port.
     */
    void showCompatibleFeedback(CVirtualPort* from);

    /**
     * Hide feedback, called when dropping a dragged wire.
     */
    void hideFeedback();

protected:
    CPort* createConnectionPort(Connection*);

private:
    PVirtualPort* m_presentation;
    QtFactory* m_factory;
    QMap<int, CPort*> m_connectedPorts;
    CPort* m_availablePort;
};

#endif // CVIRTUALPORT_H
