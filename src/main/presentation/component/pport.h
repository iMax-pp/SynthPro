#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsWidget>

class CPort;

/**
 * Represent a single port in a PPort widget.
 */
class PPort : public QGraphicsWidget {
public:
    PPort(CPort* control, QGraphicsItem* parent);

    /// Override QGraphicsWidget::paint().
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    /// @returns the associated control of type CPort.
    inline CPort* control() const { return m_control; }

    /// Default UI port size.
    static const int PORT_SIZE = 15;

    void showCompatibleFeedback();
    void showConnectableFeedback();
    void showUnconnectableFeedback();
    void hideFeedback();

    void showClickFeedback();
    void hideClickFeedback();

    void showDropFeedback();
    void showUnDropFeedback();
    void hideDropFeedback();

protected:
    // Handle drag & drop events
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

private:
    CPort* m_control;
    QPalette m_oldPalette;
};

#endif // PPORT_H
