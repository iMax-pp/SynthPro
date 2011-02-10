#ifndef CVIRTUALPORT_H
#define CVIRTUALPORT_H

#include "abstraction/virtualport.h"

class CPortWidget;
class PVirtualPort;
class QtFactory;

class CVirtualPort : public virtual VirtualPort {
    Q_OBJECT

public:
    CVirtualPort(Module* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);
    void initialize();

    void setPresentation(PVirtualPort*);
    inline PVirtualPort* presentation() const { return m_presentation; }

    void connectTo(VirtualPort* other);
    void disconnectFrom(VirtualPort* other);

    void updateWiresPositions();

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
    // Replicates this port (create a CPortWidget and its presentation)
    void replicate();

private:
    PVirtualPort* m_presentation;
    QtFactory* m_factory;
    QList<CPortWidget*> m_portWidgets;
};

#endif // CVIRTUALPORT_H
