#ifndef CVIRTUALPORT_H
#define CVIRTUALPORT_H

#include "abstraction/component/virtualport.h"
#include "presentation/component/pvirtualport.h"
#include <QHash>
#include <QPointer>

class CPort;
class QtFactory;

class CVirtualPort : public virtual VirtualPort {
    Q_OBJECT

public:
    CVirtualPort(Module* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);
    virtual ~CVirtualPort();

    void initialize();

    inline PVirtualPort* presentation() const { return m_presentation; }
    void setPresentation(PVirtualPort*);

    /**
     * Override of the base implementation providing a GUI feedback.
     * This method creates the CPorts (one for each side) and the CWire used by the new connection
     */
    Connection* connect(VirtualPort* other);
    /**
     * Connect this VirtualPort’s CPort to a given target CPort
     * This method should be called by CPort when it detects an attempt from the user to
     * make a connection.
     * @param own The CPort owned by this CVirtualPort
     * @param target The target CPort
     */
    Connection* connect(CPort* own, CPort* target);
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

    /// Remove a given CPort
    void removeConnectionPort(CPort*);

protected:
    /// Call this method to hide or show the available port of this VirtualPort (it matters if this VirtualPort is replicable or not)
    void updateAvailableFeedback();

    /// Call this method to show the “compatible” feedback of a port
    void showPortCompatibleFeedback(CPort*, bool isCompatible, bool isConnectable) const;

    /// Internal method creating a CPort for a given Connection
    CPort* createConnectionPort(Connection*);

    /// Internal method associating a CPort to a given Connection
    void setConnectionPort(Connection*, CPort*);

    /// Internal method deleting a given CPort if it’s not reconnecting
    void removeConnectionPortIfNeeded(CPort*);

private:
    QPointer<PVirtualPort> m_presentation;
    QtFactory* m_factory;

    /// Set of ports used by the connections of this VirtualPort
    QHash<CPort*, Connection*> m_connectedPorts;

    /// The CPort representing the availableness of this VirtualPort
    CPort* m_availablePort;

    // Internally used variables to handle reconnections
    CPort* m_useOwnPort;
    CPort* m_useOthersPort;
};

#endif // CVIRTUALPORT_H
