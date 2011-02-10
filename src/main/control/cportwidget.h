#ifndef CPORTWIDGET_H
#define CPORTWIDGET_H

#include <QObject>

class CPort;
class CWire;
class PortWidget;
class QPointF;
class QtFactory;

/**
 * Represents a single port
 */
class CPortWidget : public QObject {
    Q_OBJECT

public:
    CPortWidget(CPort* parent, QtFactory*);

    void setPresentation(PortWidget*);
    inline PortWidget* presentation() const { return m_presentation; }

    inline CPort* port() const { return m_port; }

    inline CWire* wire() const { return m_wire; }
    void setWire(CWire*);

    void connectTo(CPortWidget* other);
    void disconnectFrom(CPortWidget* other);

    /*
     * The presentation of this CPortWidget should call
     * these operations when the user attempts to drag and
     * drop from a PortWidget
     * TODO make these functions protected slots
     */
    void drag();
    void dragMove(const QPointF&);
    void drop(CPortWidget* target);

    void showFeedback(bool compatible);
    void hideFeedback();

protected slots:
    void unsetWire();

private:
    PortWidget* m_presentation;
    CPort* m_port;
    QtFactory* m_factory;
    CWire* m_wire;
    CWire* m_tmpWire;
};

#endif // CPORTWIDGET_H
