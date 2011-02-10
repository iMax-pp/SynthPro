#ifndef CWIRE_H
#define CWIRE_H

#include "presentation/pwire.h"

#include <QObject>

class CPortWidget;

class CWire : public QObject {
public:
    CWire();
    virtual ~CWire();

    void setPresentation(PWire*);
    inline PWire* presentation() const { return m_presentation; }

    inline CPortWidget* inPort() const { return m_inPort; }
    inline CPortWidget* outPort() const { return m_outPort; }

    void setInPort(CPortWidget*);
    void setOutPort(CPortWidget*);

    /*
     * Update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(const QPointF& = QPointF());

private:
    PWire* m_presentation;
    CPortWidget* m_inPort;
    CPortWidget* m_outPort;
};

#endif // CWIRE_H
