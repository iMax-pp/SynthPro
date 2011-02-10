#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CPortWidget;
class QtFactory;

class CPort : public virtual Port {
    Q_OBJECT

public:
    CPort(Module* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);
    void initialize();

    void setPresentation(PPort*);
    inline PPort* presentation() const { return m_presentation; }

    void connectTo(Port* other);
    void disconnectFrom(Port* other);

    void updateWiresPositions();

    /**
     * Show feedback, called when drawing a wire from a port.
     * @param The origin port.
     */
    void showFeedback(CPort* from);

    /**
     * Hide feedback, called when dropping a dragged wire.
     */
    void hideFeedback();

protected:
    // Replicates this port (create a CPortWidget and its presentation)
    void replicate();

private:
    PPort* m_presentation;
    QtFactory* m_factory;
    QList<CPortWidget*> m_portWidgets;
};

#endif // CPORT_H
