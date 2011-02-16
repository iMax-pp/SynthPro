#ifndef CVIRTUALPORT_H
#define CVIRTUALPORT_H

#include "abstraction/component/virtualport.h"
#include <QHash>

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

    /**
     * Override of the base implementation providing a GUI feedback.
     * This method creates the CPorts (one for each side) and the CWire used by the new connection
     */
    Connection* connect(VirtualPort* other);
    /// Disconnect the connection using a given CPort (this method is used by CPort)
    void disconnect(CPort*);
    /// Disconnect a given connection (and remove its presentation)
    bool disconnect(Connection*);
    // bool reconnect(Connection*, VirtualPort* other);

    /// Call this method when this module moved and you want its connections wires to move accordingly
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

    /// Remove a given CPort (without deleting it)
    void removeConnectionPort(CPort*);

protected:
    /// Call this method to hide or show the available port of this VirtualPort (it matters if this VirtualPort is replicable or not)
    void updateAvailableFeedback();

    /// Internal method creating a CPort for a given Connection
    CPort* createConnectionPort(Connection*);
    /// Internal method deleting a given CPort
    void deleteConnectionPort(CPort*);

private:
    PVirtualPort* m_presentation;
    QtFactory* m_factory;

    /// Set of ports used by the connections of this VirtualPort
    QHash<CPort*, Connection*> m_connectedPorts;

    /// The CPort representing the availableness of this VirtualPort
    CPort* m_availablePort;
};

#endif // CVIRTUALPORT_H
