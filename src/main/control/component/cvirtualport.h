#ifndef CVIRTUALPORT_H
#define CVIRTUALPORT_H

#include "abstraction/component/virtualport.h"

class PVirtualPort;
class QtFactory;

class CVirtualPort : public virtual VirtualPort {
    Q_OBJECT

public:
    CVirtualPort(Module* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);

    void setPresentation(PVirtualPort*);
    inline PVirtualPort* presentation() const { return m_presentation; }

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
    Port* replicate();
    bool removePort(Port*);

private:
    PVirtualPort* m_presentation;
    QtFactory* m_factory;
};

#endif // CVIRTUALPORT_H
