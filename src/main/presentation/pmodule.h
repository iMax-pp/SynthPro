#ifndef PMODULE_H
#define PMODULE_H

#include "presentation/layoutitem.h"
#include <QGraphicsRectItem>

class CModule;

class PModule : public QGraphicsRectItem {
public:
    PModule(CModule*);

protected:
    // Call this method to compute the layout of this item
    void doLayout();

    inline LayoutItem* in() const { return m_in; }
    inline LayoutItem* name() const { return m_name; }
    inline LayoutItem* out() const { return m_out; }
    inline LayoutItem* settings() const { return m_settings; }

    /*
     * Intercept mouse moving to update the hooked wires accordingly.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);


    CModule* m_control;
    static const qreal DEFAULT_WIDTH = 150;
    static const qreal DEFAULT_HEIGHT = 100;

private:
    LayoutItem* m_in;
    LayoutItem* m_name;
    LayoutItem* m_out;
    LayoutItem* m_settings;
    LayoutItem* m_layout;
};

#endif // PMODULE_H
