#ifndef CPORT_H
#define CPORT_H

#include "presentation/component/pport.h"
#include <QObject>
#include <QPointer>

class CVirtualPort;
class CWire;
class QPointF;
class QtFactory;

class CPort : public QObject {
    Q_OBJECT

public:
    CPort(CVirtualPort* parent, QtFactory*);
    virtual ~CPort();

    inline CVirtualPort* vPort() const { return m_vPort; }

    inline PPort* presentation() const { return m_presentation; }
    void setPresentation(PPort*);

    inline CWire* wire() const { return m_wire; }
    void setWire(CWire*);
    void createTmpWire(CPort* from, const QPointF& to);

    void disconnect();
    void reconnect(const QPointF&);

    inline bool reconnecting() const { return m_reconnecting; }

    /*
     * The presentation of this CPort should call
     * these operations when the user attempts to drag and
     * drop from a PortWidget
     * TODO make these functions protected slots
     */
    void drag(const QPointF&);
    void dragMove(const QPointF&);
    void drop(CPort* target);

    void mouseEnter();
    void mouseLeave();

    void showFeedback(bool compatible);
    void hideFeedback();

    void showAvailableFeedback();
    void hideAvailableFeedback();

private slots:
    void wireDeleted();

private:
    CVirtualPort* m_vPort;
    QPointer<PPort> m_presentation;
    QtFactory* m_factory;
    CWire* m_wire;
    CWire* m_tmpWire;
    PPort* m_clickableFeedback;
    CPort* m_reconnecting;
};

#endif // CPORT_H
