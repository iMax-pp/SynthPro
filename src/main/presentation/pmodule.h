#ifndef PMODULE_H
#define PMODULE_H

#include <QGraphicsWidget>

class CModule;
class PixmapButtonWidget;
class QGraphicsAnchorLayout;

/**
 * Presentation of a Module.
 */
class PModule : public QGraphicsWidget {
    Q_OBJECT

public:
    /// Constructs a PModule and creates its layouts.
    explicit PModule(CModule*);

    /// Overriden method to redefine the painting style.
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    /// Overriden method to include close button on shape calculation.
    QRectF boundingRect() const;

signals:
    /// Triggered when close button is clicked.
    void closeBtnClicked();

protected:
    /*
     * Intercept mouse moving to update the hooked wires accordingly.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    /// @returns the left area (usually the inports area).
    inline QGraphicsAnchorLayout* leftArea() const { return m_leftArea; }
    /// @returns the bottom area (usually the module settings area).
    inline QGraphicsAnchorLayout* bottomArea() const { return m_bottomArea; }
    /// @returns the center area (usually the title area).
    inline QGraphicsAnchorLayout* centerArea() const { return m_centerArea; }
    /// @returns the right area (usually the outports area).
    inline QGraphicsAnchorLayout* rightArea() const { return m_rightArea; }

    CModule* m_control;

private:
    QGraphicsAnchorLayout* m_leftArea;
    QGraphicsAnchorLayout* m_bottomArea;
    QGraphicsAnchorLayout* m_centerArea;
    QGraphicsAnchorLayout* m_rightArea;
    PixmapButtonWidget* m_closeBtn;
};

#endif // PMODULE_H
