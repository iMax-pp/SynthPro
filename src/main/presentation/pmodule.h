#ifndef PMODULE_H
#define PMODULE_H

#include <QGraphicsWidget>

class CModule;
class QGraphicsAnchorLayout;

class PModule : public QGraphicsWidget {
    Q_OBJECT
public:
    PModule(CModule*);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

signals:
    void closeBtnClicked();

protected:
    /*
     * Intercept mouse moving to update the hooked wires accordingly.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

    inline QGraphicsAnchorLayout* leftArea() const { return m_leftArea; }
    inline QGraphicsAnchorLayout* bottomArea() const { return m_bottomArea; }
    inline QGraphicsAnchorLayout* centerArea() const { return m_centerArea; }
    inline QGraphicsAnchorLayout* rightArea() const { return m_rightArea; }

    CModule* m_control;

private:
    QGraphicsAnchorLayout* m_leftArea;
    QGraphicsAnchorLayout* m_bottomArea;
    QGraphicsAnchorLayout* m_centerArea;
    QGraphicsAnchorLayout* m_rightArea;
};

#endif // PMODULE_H
