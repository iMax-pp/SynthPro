#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QGraphicsWidget>

class TextWidget : public QGraphicsWidget {
public:
    TextWidget(const QString& text, QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    inline const QString& text() const { return m_text; }
    inline void setText(const QString& text) { m_text = text; }

private:
    QString m_text;
};

#endif // TEXTWIDGET_H
