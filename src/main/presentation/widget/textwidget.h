#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QGraphicsWidget>

/**
 * Widget only class (no PAC involved), representing a text.
 */
class TextWidget : public QGraphicsWidget {
public:
    TextWidget(const QString& text, QGraphicsItem* parent);

    /// @returns The text on the widget.
    inline const QString text() const { return m_textitem.text(); }

    /// @param text to set the widget with.
    inline void setText(const QString& text) { m_textitem.setText(text); }

    /// @param font to use on the widget.
    void setFont(const QFont&);

private:
    QGraphicsSimpleTextItem m_textitem;
};

#endif // TEXTWIDGET_H
