#ifndef CPORT_H
#define CPORT_H

#include <QObject>

class CVirtualPort;
class CWire;
class PPort;
class QPointF;
class QtFactory;

class CPort : public QObject {
    Q_OBJECT

public:
    CPort(CVirtualPort* parent, QtFactory*);

    inline CVirtualPort* vPort() const { return m_vPort; }

    void setPresentation(PPort*);
    inline PPort* presentation() const { return m_presentation; }

    inline CWire* wire() const { return m_wire; }
    void setWire(CWire*);

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
    PPort* m_presentation;
    QtFactory* m_factory;
    CWire* m_wire;
    CWire* m_tmpWire;
    PPort* m_clickableFeedback;
};

#endif // CPORT_H
