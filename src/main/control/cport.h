#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"

class CVirtualPort;
class CWire;
class PPort;
class QPointF;
class QtFactory;

class CPort : public Port {
    Q_OBJECT

public:
    CPort(CVirtualPort* parent, QtFactory*);

    void setPresentation(PPort*);
    inline PPort* presentation() const { return m_presentation; }

    inline CWire* wire() const { return m_wire; }
    void setWire(CWire*);

    bool connect(Port* other);
    bool disconnect();

    /*
     * The presentation of this CPort should call
     * these operations when the user attempts to drag and
     * drop from a PortWidget
     * TODO make these functions protected slots
     */
    void drag();
    void dragMove(const QPointF&);
    void drop(CPort* target);

    void mouseEnter();
    void mouseLeave();

    void showFeedback(bool compatible);
    void hideFeedback();

private slots:
    void wireDeleted();
private:
    PPort* m_presentation;
    QtFactory* m_factory;
    CWire* m_wire;
    CWire* m_tmpWire;
};

#endif // CPORT_H
